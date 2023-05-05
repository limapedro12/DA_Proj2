#ifndef DA_PROJ2_GRAPH_H
#define DA_PROJ2_GRAPH_H

#include "VertexEdge.h"

#include <vector>
#include <algorithm>

bool inPath(int value, int path[], unsigned int n);

class Graph {
public:
    Vertex* findVertex(int id);
    std::vector<Vertex*> getVertexSet() const;
    void addVertex(Vertex* v);
    void addBidirectionalEdge(Vertex* source, Vertex* dest, double dist);
    void clear();
    void sort();

    void tspBacktrackingAux(int path[], int idx, unsigned int n, long cost);
    int tspBacktracking(unsigned int n, int path[]);
private:
    std::vector<Vertex*> vertexSet;
    long minCost;
    int* minPath;
};


#endif //DA_PROJ2_GRAPH_H
