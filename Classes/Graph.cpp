#include "Graph.h"

using namespace std;

Vertex* Graph::findVertex(unsigned int id) const {
    if (id > vertexSet.size()) return nullptr;
    return vertexSet[id];
}

std::vector<Vertex*> Graph::getVertexSet() const {
    return vertexSet;
}

int Graph::getNumVertex() const{
    return vertexSet.size();
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
/*
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
*/

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

int Graph::tspBacktracking(unsigned int path[]) {
    minPath = new unsigned int[vertexSet.size()];
    minCost = ULONG_MAX;
    path[0] = 0;

    tspBacktrackingAux(path, 1, 0);

    memcpy(path, minPath, sizeof(unsigned int)*vertexSet.size());
    delete minPath;
    return minCost;
}

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
            s.push({curr, i + 1, idx});
            Vertex *next_vertex = vertexSet[curr]->getAdj()[i]->getDest();
            path[idx] = vertexSet[curr]->getAdj()[i];
            if(currently_in_path.find(next_vertex->getId()) == currently_in_path.end()) {
                currently_in_path.insert(curr);
                s.push({(int) next_vertex->getId(), 0, idx + 1});
            }
        } else {
            currently_in_path.erase(curr);
        }
    }
    return false;
}

vector<Edge*> Graph::RandomPath3(){
    cout << "Starting RandomPath\n";
    vector<Edge*> path(vertexSet.size());

    if(RandomPathAux3(path)) {
        cout << "Done RandomPath\n";
        return path;
    }
    else {
        return {};
    }
}

double haversine(double lat1, double lon1,
                 double lat2, double lon2){
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);

    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

vector<Edge*> Graph::RandomPath4() {
    cout << "Starting RandomPath\n";
    vector<Edge*> path(vertexSet.size());
    for(int i = 0; i < vertexSet.size(); i++){
        int next = (i+1) % vertexSet.size();
        Edge* e = get_edge(*this, i, next);
        if(e == nullptr){
            double dist = haversine(vertexSet[i]->getLat(), vertexSet[i]->getLon(),
                                    vertexSet[next]->getLat(), vertexSet[next]->getLon());
            e = new Edge(vertexSet[i], vertexSet[next], dist);
            Edge* reverse = new Edge(vertexSet[next], vertexSet[i], dist);
            e->setReverse(reverse);
            reverse->setReverse(e);
        }
        path[i] = e;
    }
    cout << "Done RandomPath\n";
    return path;
};

void Graph::print() const {
    for (Vertex* v : vertexSet) v->print();
}


