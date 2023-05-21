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

bool inPath(unsigned int value, unsigned int path[], unsigned int n);

class Graph {
public:
    Vertex* findVertex(unsigned int id) const;
    std::vector<Vertex*> getVertexSet() const;
    void addVertex(Vertex* v);
    void addBidirectionalEdge(Vertex* source, Vertex* dest, double dist);
    void clear();

    bool RandomPathAux(std::vector<Edge*> &path, unsigned int idx);
    std::vector<Edge*> RandomPath();
    std::vector<Edge*> RandomPath2();
    std::vector<Edge*> NearestPointsPath();
    bool RandomPathAux3(std::vector<Edge*> &path);
    std::vector<Edge*> RandomPath3();

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
std::vector<Edge*> improvePath(std::vector<Edge*> path, Graph g);

#endif //DA_PROJ2_GRAPH_H
