//
// graph.cpp
// Author: Logan K. Leavitt
// implementation file for the graph class
//

#include <iostream>
#include <vector>
#include "graph.h"
#include "polygon.h"

// Default Constructor
Graph::Graph() : adjacency_list() {}

// Paramterized Constructor
// n = number of nodes
Graph::Graph(int n) : adjacency_list(n) {}

// Constructor from a Polygon
// Makes the necessary edges
Graph::Graph(const Polygon & p) :
    adjacency_list(p.numVertices())
{
    for (int i = 0; i < numNodes(); i++) {
        adjacency_list[i].push_back((i - 1 + numNodes()) % numNodes());
        adjacency_list[i].push_back((i + 1) % numNodes());
    }
}

// adds edge between a and b
// (undirected graph so a's list and b's list are affected
void Graph::addEdge(int a, int b) {
    adjacency_list[a].push_back(b);
    adjacency_list[b].push_back(a);
}

// gets the number of nodes
int Graph::numNodes() {
    return adjacency_list.size();
}

// Insertion operator overload
std::ostream & operator<<(std::ostream & os, const Graph & g) {
    int i = 0;
    for (auto it = g.adjacency_list.begin(); it != g.adjacency_list.end(); ++it) {
        os << i++ << ": ";
        for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
            os << *it2 << " ";
        }
        os << std::endl;
    }

    return os;
}
