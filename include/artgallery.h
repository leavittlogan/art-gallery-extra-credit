//
// artgallery.h
// Author: Logan K. Leavitt
// Header file for the Art Gallery class which solves the Art Gallery Problem
//

#ifndef ARTGALLERY_H
#define ARTGALLERY_H

#include <iostream>
#include <vector>
#include "polygon.h"
#include "graph.h"

class ArtGallery {
    public:
        ArtGallery(const Polygon & p);

        friend std::ostream & operator<<(std::ostream & os, const ArtGallery & a);

        const std::vector<Point> & getGuards() const;

    private:
        Polygon polygon;
        Graph graph;
        std::vector<int> colors;
        std::vector<Point> guards;
        int size;
        bool valid;

        void solve();
        void placeGuards();
        bool isConcave(Point a, Point b, Point c);
        bool isEar(int i, const std::vector<int> & tempPoly, const std::vector<bool> & concave);
        bool isInside(Point p, Point a, Point b, Point c);
};

#endif // ARTGALLERY_H
