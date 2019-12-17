//
// artgallery.cpp
// Author: Logan K. Leavitt
// implementation file for the art gallery class
//

#include <iostream>
#include <exception>
#include <vector>
#include <stack>
#include "artgallery.h"
#include "graph.h"
#include "polygon.h"

// struct to store the ear that was removed and its connections
// 0: ear that was removed
// 1 and 2: connections
struct Ear {
    int ear, p1, p2;
    Ear() {}
    Ear(int ear, int p1, int p2) : ear(ear), p1(p1), p2(p2) {}
};

// Constructor
ArtGallery::ArtGallery(const Polygon & p) :
    polygon(p),
    graph(p),
    colors(p.numVertices(), 0),
    size(p.numVertices()),
    valid(false)
{
    if (size >= 3) {
        solve();
        valid = true;
    }
}

// Insertion operator overload
// Used for more detailed output
std::ostream & operator<<(std::ostream & os, const ArtGallery & a) {
    os << "Adjacency List:"<< std::endl << a.graph;

    os << "Colors of vertices:" << std::endl;
    for (int i = 0; i < a.size; i++) {
        os << i << ": ";
        switch (a.colors[i]) {
            case 1:
                os << "red";
                break;
            case 2:
                os << "green";
                break;
            case 3:
                os << "blue";
                break;
            default:
                os << "no color";
                break;
        }
        os << std::endl;
    }

    os << "Guards:" << std::endl;
    for (auto it = a.guards.begin(); it != a.guards.end(); ++it) {
        os << *it << " ";
    }

    return os;
}

// getter function for the guards list
const std::vector<Point> & ArtGallery::getGuards() const {
    return guards;
}

// function which implements my solution for the art gallery problem
// Uses and adaptation of the ear clipping algorithm
void ArtGallery::solve() {
    // check which points are concave
    std::vector<bool> concave(size, false);
    for (int i = 0; i < size; i++) {
        concave[i] = isConcave(
                polygon[(i - 1 + size) % size],
                polygon[i],
                polygon[(i + 1) % size]
        );
    }

    // integers in tempPoly represent indices of the original polygon
    std::vector<int> tempPoly(size);
    for (int i = 0; i < size; i++) tempPoly[i] = i;

    int i = 0;
    int runs_without_ear = 0;
    std::stack<Ear> ears;
    while (tempPoly.size() > 3) { // while not a triangle

        // throw logic error if all points have been iterated through and no ear is found
        if (runs_without_ear == tempPoly.size()) throw std::logic_error("No ear found");

        // if vertex is an ear, remove it and add to stack
        if (concave[tempPoly[i]] && isEar(i, tempPoly, concave)) { 
            int i_prev = (i - 1 + tempPoly.size()) % tempPoly.size();
            int i_next = (i + 1) % tempPoly.size();

            // add ear to stack
            ears.push(Ear(
                        tempPoly[i],
                        tempPoly[i_prev],
                        tempPoly[i_next]
            ));


            // add edge to graph
            graph.addEdge(tempPoly[i_prev], tempPoly[i_next]);

            // remove ear from polygon
            tempPoly.erase(tempPoly.begin() + i);

            // check concavity of adjacent vertices
            concave[tempPoly[i_prev]] = isConcave(
                polygon[tempPoly[(i_prev - 1 + tempPoly.size()) % tempPoly.size()]],
                polygon[tempPoly[i_prev]],
                polygon[tempPoly[(i_prev + 1) % tempPoly.size()]]
            );
            
            i = i % tempPoly.size();
            concave[tempPoly[i]] = isConcave(
                polygon[tempPoly[i_prev]],
                polygon[tempPoly[i]],
                polygon[tempPoly[(i + 1) % tempPoly.size()]]
            );


            runs_without_ear = 0;
        } else {
            i = (i + 1) % tempPoly.size();
            runs_without_ear++;
        }
    }

    // color resulting triangle
    for (int i = 0; i < 3; i++) {
        colors[tempPoly[i]] = i + 1;
    }

    // pop ears from stack one by one, and color in the only way possible
    Ear ear;
    while (!ears.empty()) {
        ear = ears.top();

        if (colors[ear.p1] != 1 && colors[ear.p2] != 1) {
            colors[ear.ear] = 1;
        } else if (colors[ear.p1] != 2 && colors[ear.p2] != 2) {
            colors[ear.ear] = 2;
        } else {
            colors[ear.ear] = 3;
        }
        
        ears.pop();
    }

    placeGuards();
}

// places guards, assuming the vertices have all been colored
void ArtGallery::placeGuards() {
    std::vector<std::vector<Point>> guardsByColor(3, std::vector<Point>(0));

    for (int i = 0; i < size; ++i) {
        guardsByColor[colors[i] - 1].push_back(polygon[i]);
    }

    int minColor = (guardsByColor[0].size() > guardsByColor[1].size()) ? 1 : 0;
    minColor = (guardsByColor[minColor].size() > guardsByColor[2].size()) ? 2 : minColor;

    guards = guardsByColor[minColor];
}

// checks if a point is concave by taking a determinant
// this works because determinants give you signed area of the
// parallelogram formed by two vectors
bool ArtGallery::isConcave(Point a, Point b, Point c) {
    return (((b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x)) > 0);
}

// checks if vertex is an ear
bool ArtGallery::isEar(int p, const std::vector<int> & tempPoly, const std::vector<bool> & concave) {
    int p_prev = (p - 1 + tempPoly.size()) % tempPoly.size();
    int p_next = (p + 1) % tempPoly.size();

    Point p1 = polygon[tempPoly[p_prev]];
    Point p2 = polygon[tempPoly[p]];
    Point p3 = polygon[tempPoly[p_next]];
    for (int i = (p + 2) % tempPoly.size(); i != p_prev; i = (i + 1) % tempPoly.size()) {
        if (!concave[tempPoly[i]]) {
            if (isInside(polygon[tempPoly[i]], p1, p2, p3)) return false;
        }
    }

    return true;
}

// checks if a point p lies inside triangle (a, b, c)
bool ArtGallery::isInside(Point p, Point a, Point b, Point c) {
    double area = 0.5 * (-b.y * c.x + a.y * (-b.x + c.x) + a.x * (b.y - c.y) + b.x * c.y);
    double sign = area < 0 ? -1 : 1;
    double s = (a.y * c.x - a.x * c.y + (c.y - a.y) * p.x + (a.x - c.x) * p.y) * sign;
    double t = (a.x * b.y - a.y * b.x + (a.y - b.y) * p.x + (b.x - a.x) * p.y) * sign;

    return s > 0 && t > 0 && (s + t) < 2 * area * sign;
}

