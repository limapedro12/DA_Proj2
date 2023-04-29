#include "Graph.h"

Vertex* binarySearch(int id, const std::vector<Vertex*>& v, int low, int high) {
    while (low <= high) {
        int m = low + (high - low) / 2;

        if (v[m]->getId() == id) return v[m];
        else if (v[m]->getId() < id) low = m + 1;
        else high = m - 1;
    }

    return nullptr;
}

Vertex* Graph::findVertex(int id) {
    if (vertexSet.empty()) return nullptr;
    return binarySearch(id, vertexSet, 0, vertexSet.size() - 1);
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
