//
// graph.h
// Author: Logan K. Leavitt
// header file for a basic graph class
//

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include "polygon.h"

class Graph {
    public:
        Graph();
        Graph(int n);
        Graph(const Polygon & p);

        void addEdge(int a, int b);
        int numNodes();

        friend std::ostream & operator<<(std::ostream & os, const Graph & g);

    private:
        std::vector<std::vector<int>> adjacency_list;
};

#endif
