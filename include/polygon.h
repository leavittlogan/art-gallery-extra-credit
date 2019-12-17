//
// polygon.h
// Author: Logan K. Leavitt
// header file for the polygon class
//

#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <vector>

struct Point {
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    double x, y;
};

std::ostream & operator<<(std::ostream & os, const Point & p);

class Polygon {
    friend std::ostream & operator<<(std::ostream & os, const Polygon & p);

    public:
        void push(double x, double y);
        void clear();
        int numVertices() const;

        Point & operator[](int i);
        const Point & operator[](int i) const;

    private:
        std::vector<Point> pointList;
};


#endif // POLYGON_H
