#include "Graph.h"

Vertex* Graph::findVertex(int id) {
    return vertexSet[id];
}

std::vector<Vertex*> Graph::getVertexSet() const {
    return vertexSet;
}

void Graph::addVertex(Vertex *v) {
    vertexSet.push_back(v);
}

void Graph::addBidirectionalEdge(Vertex *source, Vertex *dest, double dist) {
    Edge* e1 = source->addEdge(dest, dist);
    Edge* e2 = dest->addEdge(source, dist);

    e1->setReverse(e2);
    e2->setReverse(e1);
}

void Graph::clear() {
    vertexSet.clear();
}

void Graph::sort() {
    std::sort(vertexSet.begin(), vertexSet.end(), [](Vertex* a, Vertex* b) {
        return a->getId() < b->getId();
    });
}
