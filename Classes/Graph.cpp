#include "Graph.h"

#include <algorithm>
#include <random>
#include <stdio.h>
#include <vector>

using namespace std;

Vertex* Graph::findVertex(unsigned int id) const{
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
    if(n == 0)
        return false;
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

Edge* get_edge(const Graph& g, int src, int dest){
    return get_edge(g.findVertex(src), g.findVertex(dest));
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
        printf("%d[ %3d, %3d], ", path[i]->getSource()->getId(), path[i]->getSource(), path[i]->getSource()->getLon());
    }
    printf("%d[ %3d, %3d]", path.back()->getDest()->getId(), path.back()->getDest()->getLat(), path.back()->getDest()->getLon());
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
            else
                cout << "Path failed\n";
        }
    }
    return false;
}

vector<Edge*> Graph::RandomPath(){
    cout << "Starting RandomPath\n";
    vector<Edge*> path(vertexSet.size());
    bool isDone = true;

    if(RandomPathAux(path, 0)) {
        cout << "Done RandomPath\n";
        return path;
    }
    else {
        return vector<Edge *>();
    }
}

// Make a random path that starts and ends in the same point and goes through all the points in the graph
vector<Edge*> Graph::RandomPath2(){
    vector<Edge*> path;
    bool notDone = true;
    bool breakLoop = false;
    while(notDone) {
        vector<unordered_set<Edge*>> vertices;
        vertices.reserve(vertexSet.size());
        for(Vertex* v : vertexSet){
            unordered_set<Edge*> vus;
            for(Edge* e : v->getAdj()){
                if(e->getDest()->getId() == 0)
                    continue;
                vus.insert(e);
            }
            vertices.push_back(vus);
        }

        path.clear();
        int n = vertexSet.size();
        int i = 0;
        Vertex* curr = vertexSet[0];
        while (i < n - 1) {
            unordered_set<Edge *> adj = vertices[curr->getId()];
            if(adj.empty()){
                cout << "Empty adj\n";
                breakLoop = true;
                break;
            }
            int idx = rand() % adj.size();
            auto e_itr = adj.begin();
            for(int j = 0; j < idx; j++)
                e_itr++;
            Edge* e = *e_itr;
            for(Edge* e2 : adj){
                vertices[e2->getDest()->getId()].erase(e2->getReverse());
            }
            vertices[curr->getId()].clear();
            path.push_back(e);
            curr = e->getDest();
            i++;
        }
        if(breakLoop){
            breakLoop = false;
            continue;
        }
        cout << "Almost done\n";
        Edge *e = get_edge(*this, path.back()->getDest()->getId(), 0);
        if (e == nullptr) {
            double dist = sqrt(pow(path.back()->getDest()->getLat() - vertexSet[0]->getLat(), 2) +
                               pow(path.back()->getDest()->getLon() - vertexSet[0]->getLon(), 2));
            e = new Edge(path.back()->getDest(), vertexSet[0], dist);
        }
        if (e != nullptr) {
            notDone = false;
            path.push_back(e);
        }
    }
    return path;
}

vector<Edge*> Graph::NearestPointsPath(){
    struct comp { bool operator()(Edge* e1, Edge* e2){
            return e1->getDist() < e2->getDist();
    }};
    vector<Edge*> path;
    bool notDone = true;
    bool breakLoop = false;
    while(notDone) {
//        cout << "Still not done\n";
        vector<priority_queue<Edge*, vector<Edge*>, comp>> vertices;
        vertices.reserve(vertexSet.size());
        for(Vertex* v : vertexSet){
            priority_queue<Edge*, vector<Edge*>, comp> vpq;
            for(Edge* e : v->getAdj()){
//                cout << "Pushing " << e->getSource()->getId() << " -> " << e->getDest()->getId() << endl;
                if(e->getDest()->getId() == 0)
                    continue;
                vpq.push(e);
            }
            vertices.push_back(vpq);
        }
        unordered_set<int> visited;

        path.clear();
        int n = vertexSet.size();
        int i = 0;
        Vertex* curr = vertexSet[0];
        while (i < n - 1) {
            priority_queue<Edge *, vector<Edge *>, comp> adj = vertices[curr->getId()];
            if(adj.empty())
                return vector<Edge*>();
            Edge* e = adj.top();
            adj.pop();
            while(visited.find(e->getDest()->getId()) != visited.end()){
                if(adj.empty())
                    return vector<Edge*>();
//                cout << "Popping " << adj.top()->getDest()->getId() << endl;
//                cout << "Size: " << adj.size() << endl;
                e = adj.top();
                adj.pop();
            }
            visited.insert(e->getDest()->getId());
            path.push_back(e);
            curr = e->getDest();
            i++;
//            cout << e->getDest()->getId() << endl;
        }
        if(breakLoop){
            cout << "Break\n";
            breakLoop = false;
            continue;
        }
//        cout << "Almost done\n";
        Edge *e = get_edge(*this, path.back()->getDest()->getId(), 0);
        if (e != nullptr) {
            notDone = false;
            path.push_back(e);
        } else {
            return vector<Edge*>();
        }
    }
//    cout << "Done\n";
    return path;
}


// auto [currId, currIdx] = stateStack.top();
//        Vertex* curr = vertexSet[currId];
//        stateStack.pop();
//
//        if (currIdx == idx) {
//            if (idx == vertexSet.size() - 1) {
//                for (Edge* e : curr->getAdj()) {
//                    if (e->getDest()->getId() == 0) {
//                        path[idx] = e;
//                        return true;
//                    }
//                }
//                continue;
//            }
//
//            bool found = false;
//            for (Edge* e : curr->getAdj()) {
//                Vertex* v = e->getDest();
//                if (!inPath(v->getId(), path, idx)) {
//                    path[idx] = e;
//                    stateStack.push({v->getId(), currIdx + 1});
//                    found = true;
//                    break;
//                }
//            }
//            if (!found) {
//                continue;
//            }
//        }
//
//        stateStack.push({curr->getId(), currIdx});

//unordered_set<int> u;
//    while(!s.empty()){
//        Vertex* v = vertexSet[s.top()];
//        s.pop();
//        u.insert(v->getId());
//        if(u.size() == vertexSet.size())
//            break;
//        for(Edge* e: v->getAdj()) {
//            int dest = e->getDest()->getId();
//            if (u.find(dest) == u.end())
//                s.push(e->getDest()->getId());
//        }
//        u.erase(v->getId());
//    }

//stack<int> s;
//    s.push(0);
//    while(!s.empty()) {
//        while (add) {
//            s.push();
//            if (dont add)
//                break;
//        }
//        while(remove) {
//            curr = s.top();
//            s.pop()
//            if(dont remove)
//                break;
//        }
//    }

struct func_call{
    int vertex;
    int for_number;
    int index;
};

bool Graph::RandomPathAux3(vector<Edge*> &path){
    stack<func_call> s;
    s.push({0, 0, 0});
    unordered_set<int> currently_in_path;
    currently_in_path.insert(0);
//    cout << "Insert - ";
//    for(auto v: currently_in_path)
//        cout << v << " ";
//    cout << endl;
    while(!s.empty()) {
            int curr = s.top().vertex;
            int i = s.top().for_number;
            int idx = s.top().index;
            s.pop();

            if (idx == vertexSet.size() - 1){
                Edge* e = get_edge(*this, curr, 0);
                if(e != nullptr) {
                    path[idx] = e;
                    return true;
                }
            }

            auto adj = vertexSet[curr]->getAdj();
            if (i < adj.size()) {
//                cout << "Add to stack: " << curr << " " << i + 1 << " " << idx << endl;
                s.push({curr, i + 1, idx});
                Vertex *next_vertex = vertexSet[curr]->getAdj()[i]->getDest();
                path[idx] = vertexSet[curr]->getAdj()[i];
                if(currently_in_path.find(next_vertex->getId()) == currently_in_path.end()) {
                    currently_in_path.insert(curr);
//                    cout << "Insert - ";
//                    for(auto v: currently_in_path)
//                        cout << v << " ";
//                    cout << endl;
//
//                    cout << "Add to stack: " << next_vertex->getId() << " " << 0 << " " << idx + 1 << endl;
                    s.push({(int) next_vertex->getId(), 0, idx + 1});
                }
            } else {
                currently_in_path.erase(curr);
                cout << "Poping " << curr << endl;
//                cout << "Erase - ";
//                for(auto v: currently_in_path)
//                    cout << v << " ";
//                cout << endl;
            }
//        while(remove) {
//            s.pop()
//            if(dont remove)
//                break;
//        }
    }
    return false;
}


vector<Edge*> Graph::RandomPath3(){
    cout << "Starting RandomPath\n";
    vector<Edge*> path(vertexSet.size());
    bool isDone = true;

    if(RandomPathAux3(path)) {
        cout << "Done RandomPath\n";
        return path;
    }
    else {
        return vector<Edge *>();
    }
}


vector<Edge*> improvePath(vector<Edge*> path, Graph g){
    double curLength = pathLengthSq(path);
    int n = path.size();
    bool foundImprovement = true;
    cout << "Starting 2-opt\n";
    vector<unordered_map<int, double>> adj(n);
    for(int i = 0; i < n; i++){
        for(Edge* e: g.getVertexSet()[i]->getAdj()){
            adj[i].insert({e->getDest()->getId(), e->getDist()});
        }
    }
    while (foundImprovement) {
//        cout << "More 2-opt\n";
        foundImprovement = false;
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
//                auto e1 = get_edge(path[i]->getSource(), path[j]->getSource());
                auto e1 = adj[path[i]->getSource()->getId()].find(path[j]->getSource()->getId());
                auto end1 = adj[path[i]->getSource()->getId()].end();
//                auto e2 = get_edge(path[i]->getDest(), path[j]->getDest());
                auto e2 = adj[path[i]->getDest()->getId()].find(path[j]->getDest()->getId());
                auto end2 = adj[path[i]->getDest()->getId()].end();
                if(e1 == end1 || e2 == end2)
                    continue;

                double lengthDelta = -path[i]->getDist() - path[j]->getDist() + e2->second + e1->second;
                lengthDelta = ::round(lengthDelta*100)/100;

                // If the length of the path is reduced, do a 2-opt swap
                if (lengthDelta < 0) {
                    if(!do2Opt(path, i, j))
                        continue;
//                    cout << i << ", " << j << " - " << lengthDelta << endl;
                    curLength += lengthDelta;
                    foundImprovement = true;
                }
            }
        }
    }
    cout << "Done 2-opt\n";
    return path;
}

