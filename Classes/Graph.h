#ifndef DA_PROJ2_GRAPH_H
#define DA_PROJ2_GRAPH_H

#include "VertexEdge.h"

#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>

bool inPath(unsigned int value, unsigned int path[], unsigned int n);

class Graph {
public:
    Vertex* findVertex(unsigned int id);
    std::vector<Vertex*> getVertexSet() const;
    void addVertex(Vertex* v);
    void addBidirectionalEdge(Vertex* source, Vertex* dest, double dist);
    void clear();

    //int pathCost(unsigned int path[]) const;
    //int tspBruteForce(unsigned int path[]) const;

    void tspBacktrackingAux(unsigned int path[], unsigned int idx, unsigned long cost);
    int tspBacktracking(unsigned int path[]);

    void print() const;
private:
    std::vector<Vertex*> vertexSet;
    unsigned long minCost;
    unsigned int* minPath;
};


#endif //DA_PROJ2_GRAPH_H
