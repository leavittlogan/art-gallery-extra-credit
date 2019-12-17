//
// polygon.cpp
// Author: Logan K. Leavitt
// implementation file
// 

#include <iostream>
#include <vector>
#include "polygon.h"

// Insertion operator overload for a Polygon
std::ostream & operator<<(std::ostream & os, const Polygon & p) {
    for (auto it = p.pointList.begin(); it != p.pointList.end(); ++it) {
        os << *it << std::endl;
    }

    return os;
}

// Insertion operator for a Point
std::ostream & operator<<(std::ostream & os, const Point & p) {
    os << "(" << p.x << ", " << p.y << ")";

    return os;
}

// pushs a point onto the back of the point list
void Polygon::push(double x, double y) {
    pointList.push_back(Point(x, y));
}

// clears the list
void Polygon::clear() {
    pointList.clear();
}

// gets the number of vertices of the polygon
int Polygon::numVertices() const {
    return pointList.size();
}

// [] operator overload
Point & Polygon::operator[](int i) {
    return pointList[i];
}

// const [] operator overload
const Point & Polygon::operator[](int i) const {
    return pointList[i];
}
