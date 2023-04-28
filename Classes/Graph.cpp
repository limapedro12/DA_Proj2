#include "Graph.h"

Vertex* Graph::findVertex(int id) {
    for (Vertex* v : vertexSet) if (v->getId() == id) return v;

    return nullptr;
}

void Graph::addVertex(Vertex *v) {
    vertexSet.push_back(v);
}
