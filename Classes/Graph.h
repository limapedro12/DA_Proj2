#ifndef DA_PROJ2_GRAPH_H
#define DA_PROJ2_GRAPH_H

#include "VertexEdge.h"

#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <random>
#include <cstdio>
#include <vector>

struct comp { bool operator()(Edge* e1, Edge* e2){
    return e1->getDist() < e2->getDist();
}};

class Graph {
public:
    Vertex* findVertex(unsigned int id) const;
    std::vector<Vertex*> getVertexSet() const;
    int getNumVertex() const;
    void addVertex(Vertex* v);
    void addBidirectionalEdge(Vertex* source, Vertex* dest, double dist);
    void clear();

    bool RandomPathAux3(std::vector<Edge*> &path);
    std::vector<Edge*> RandomPath3();
    std::vector<Edge*> RandomPath4();

    void tspBacktrackingAux(unsigned int path[], unsigned int idx, unsigned long cost);
    int tspBacktracking(unsigned int path[]);
private:
    std::vector<Vertex*> vertexSet;
    unsigned long minCost;
    unsigned int* minPath;
};

bool inPath(unsigned int value, unsigned int path[], unsigned int n);
Edge* get_edge(Vertex* src, Vertex* dest);
Edge* get_edge(const Graph& g, int src, int dest);
double haversine(double lat1, double lon1, double lat2, double lon2);

#endif //DA_PROJ2_GRAPH_H
