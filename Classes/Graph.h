#ifndef DA_PROJ2_GRAPH_H
#define DA_PROJ2_GRAPH_H

#include "VertexEdge.h"

#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

bool inPath(unsigned int value, unsigned int path[], unsigned int n);

class Graph {
public:
    Vertex* findVertex(unsigned int id);
    std::vector<Vertex*> getVertexSet() const;
    void addVertex(Vertex* v);
    void addBidirectionalEdge(Vertex* source, Vertex* dest, double dist);
    void clear();

    bool RandomPathAux(std::vector<Edge*> &path, unsigned int idx);
    std::vector<Edge*> RandomPath();

    void tspBacktrackingAux(unsigned int path[], unsigned int idx, unsigned long cost);
    int tspBacktracking(unsigned int path[]);
private:
    std::vector<Vertex*> vertexSet;
    unsigned long minCost;
    unsigned int* minPath;
};

int pathLengthSq(std::vector<Edge*> &path);
bool do2Opt(std::vector<Edge*> &path, int i, int j);
void printPath(std::string pathName, std::vector<Edge*> &path);
std::vector<Edge*> createRandomPath(Graph g);
std::vector<Edge*> improvePath(std::vector<Edge*> path);

#endif //DA_PROJ2_GRAPH_H
