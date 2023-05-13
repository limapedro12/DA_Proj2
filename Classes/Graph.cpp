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

int Graph::pathCost(unsigned int path[]) const {
    int cost = 0;
    bool change;
    for (size_t i = 0; i < vertexSet.size() - 2; i++) {
        change = false;
        Vertex* v = vertexSet[i];
        Vertex* w = vertexSet[i + 1];
        for (Edge* e : v->adj) {
            if (e->getDest()->getId() == w->getId()) {
                change = true;
                cost += e->getDist();
                break;
            }
        }
        if (!change) return INT_MAX;
    }

    Vertex* source = vertexSet[0];
    change = false;
    for (Edge* e : source->adj) {
        if (e->getDest()->getId() == path[0]) {
            change = true;
            cost += e->getDist();
            break;
        }
    }
    if (!change) return INT_MAX;

    Vertex* ending = path[vertexSet.size() - 1];
    change = false;
    for (Edge* e : ending->adj) {
        if (e->getDest() == source) {
            change = true;
            cost += e->getDist();
            break;
        }
    }
    if (!change) return INT_MAX;

    return cost;
}

int Graph::tspBruteForce(unsigned int path[]) const {
    path[0] = 0;

    int minCost = INT_MAX;
    
    minPath = new unsigned int[vertexSet.size() - 1];

    for (size_t i = 1; i < vertexSet.size(); i++) minPath[i - 1] = vertexSet[i]->getId();

    do {
        int current_cost = pathCost(minPath);
        if (current_cost < minCost) {
            memcpy(path + sizeof(unsigned int), minPath, sizeof(unsigned int)*vertexSet.size());
            minCost = current_cost;
        }
    } while (std::next_permutation(minPath));

    return minCost;
}

void Graph::tspBacktrackingAux(unsigned int path[], unsigned int idx, unsigned long cost) const {
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

int Graph::tspBacktracking(unsigned int path[]) const {
    minPath = new unsigned int[vertexSet.size()];
    minCost = ULONG_MAX;
    path[0] = 0;

    tspBacktrackingAux(path, 1, 0);

    memcpy(path, minPath, sizeof(unsigned int)*vertexSet.size());
    delete minPath;
    return minCost;
}
