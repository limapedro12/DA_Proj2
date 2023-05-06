#include "Graph.h"

Vertex* Graph::findVertex(unsigned int id) {
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

bool inPath(unsigned int value, unsigned int path[], unsigned int n) {
    for (size_t i = 0; i < n; i++)
        if (path[i] == value)
            return true;
    return false;
}

void Graph::tspBacktrackingAux(unsigned int path[], unsigned int idx, unsigned long cost){
    unsigned int cenas = path[idx-1];
    Vertex* curr = vertexSet[cenas];
    if(idx == vertexSet.size()){
        bool foundZero = false;
        for(Edge* e : curr->getAdj()){
            if(e->getDest()->getId() == 0){
                cost += e->getDist();
                foundZero = true;
                break;
            }
        }
        if(!foundZero)
            return;
        if(cost < minCost){
            minCost = cost;
            memcpy(minPath, path, sizeof(unsigned int)*vertexSet.size());
        }
        return;
    }

    if(cost >= minCost)
        return;

    for(Edge* e : curr->getAdj()){
        Vertex* v = e->getDest();
        if(!inPath(v->getId(), path, idx)){
            path[idx] = v->getId();
            tspBacktrackingAux(path, idx+1, cost + e->getDist());
        }
    }
}

int Graph::tspBacktracking(unsigned int path[]){
    minPath = new unsigned int[vertexSet.size()];
    minCost = ULONG_MAX;
    path[0] = 0;

    tspBacktrackingAux(path, 1, 0);

    memcpy(path, minPath, sizeof(unsigned int)*vertexSet.size());
    return minCost;
}

