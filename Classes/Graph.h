#ifndef DA_PROJ2_GRAPH_H
#define DA_PROJ2_GRAPH_H

#include "VertexEdge.h"

#include <vector>

class Graph {
public:
    Vertex* findVertex(int id);
    void addVertex(Vertex* v);
private:
    std::vector<Vertex*> vertexSet;
};


#endif //DA_PROJ2_GRAPH_H
