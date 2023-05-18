#include "Graph.h"

#include <algorithm>
#include <random>
#include <stdio.h>
#include <vector>

using namespace std;

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

bool inPath(unsigned int value, vector<Edge*> path, unsigned int n) {
    for (size_t i = 0; i < n; i++)
        if (path[i]->getSource()->getId() == value)
            return true;
    if(path[n-1]->getDest()->getId() == value)
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
    delete minPath;
    return minCost;
}

// Calculate the distance of the whole path (Squared Distances between points)
int pathLengthSq(vector<Edge*> &path) {
    int length = 0;
    for (int i = 0; i < path.size(); i++) {
        length += path[i]->getDist()*path[i]->getDist();
    }
    return length;
}

Edge* get_edge(Vertex* src, Vertex* dest){
    for(Edge* e : src->getAdj()){
        if(e->getDest() == dest)
            return e;
    }
    return nullptr;
}

// Perform a 2-opt swap
bool do2Opt(vector<Edge*> &path, int i, int j) {
    Edge* e_first = get_edge(path[i]->getSource(), path[j]->getSource());
    Edge* e_last = get_edge(path[i]->getDest(), path[j]->getDest());
    if(e_first == nullptr || e_last == nullptr)
        return false;

    // Reverse path[i+1] to path[j]
    for(int k = 0; k < (j-i)/2; k++){
        Edge* temp = path[i+1+k];
        path[i+1+k] = path[j-1-k]->getReverse();
        path[j-1-k] = temp->getReverse();
    }
    path[i] = e_first;
    path[j] = e_last;
    return true;
}

// Print the path.
void printPath(string pathName, vector<Edge*> &path) {
    cout << pathName << " = [";
    for (int i = 0; i < path.size(); i++) {
        if (i % 10 == 0) {
            cout << "\n    ";
        }
        printf("[ %3d, %3d], ", path[i]->getSource(), path[i]->getSource()->getLon());
    }
    printf("[ %3d, %3d]", path.back()->getDest()->getLat(), path.back()->getDest()->getLon());
    printf("\n];\n");
}

// Create a random path with all the points in graph g that starts and ends in the same point
bool Graph::RandomPathAux(vector<Edge*> &path, unsigned int idx){
    Vertex* curr;
    if(idx == 0)
        curr = vertexSet[0];
    else
        curr = path[idx-1]->getDest();
    if(idx == vertexSet.size()-1){
        for(Edge* e : curr->getAdj()){
            if(e->getDest()->getId() == 0){
                path[idx] = e;
                return true;
            }
        }
        return false;
    }

    for(Edge* e : curr->getAdj()){
        Vertex* v = e->getDest();
        if(!inPath(v->getId(), path, idx)){
            path[idx] = e;
            if(RandomPathAux(path, idx+1))
                return true;
        }
    }
    return false;
}

vector<Edge*> Graph::RandomPath(){
    vector<Edge*> path(vertexSet.size());
    bool isDone = true;

    if(RandomPathAux(path, 0))
        return path;
    else
        return vector<Edge*>();
}


vector<Edge*> improvePath(vector<Edge*> path){
    double curLength = pathLengthSq(path);
    int n = path.size();
    bool foundImprovement = true;
    while (foundImprovement) {
        foundImprovement = false;
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                Edge* e1 = get_edge(path[i]->getSource(), path[j]->getSource());
                Edge* e2 = get_edge(path[i]->getDest(), path[j]->getDest());
                if(e1 == nullptr || e2 == nullptr)
                    continue;

                double lengthDelta = -path[i]->getDist() - path[j]->getDist() + e2->getDist() + e1->getDist();

                // If the length of the path is reduced, do a 2-opt swap
                if (lengthDelta < 0) {
                    if(!do2Opt(path, i, j))
                        continue;
                    curLength += lengthDelta;
                    foundImprovement = true;
                }
            }
        }
    }
    return path;
}

