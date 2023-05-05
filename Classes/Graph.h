#ifndef DA_PROJ2_GRAPH_H
#define DA_PROJ2_GRAPH_H

#include "VertexEdge.h"

#include <vector>
#include <algorithm>

class Graph {
public:
    Vertex* findVertex(int id);
    std::vector<Vertex*> getVertexSet() const;
    void addVertex(Vertex* v);
    void addBidirectionalEdge(Vertex* source, Vertex* dest, double dist);
    void clear();
    void sort();
private:
    std::vector<Vertex*> vertexSet;
};


#endif //DA_PROJ2_GRAPH_H
