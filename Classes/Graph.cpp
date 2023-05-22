#include "Graph.h"

using namespace std;

Vertex* Graph::findVertex(unsigned int id) const{
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

int Graph::tspBacktracking(unsigned int path[]){
    minPath = new unsigned int[vertexSet.size()];
    minCost = ULONG_MAX;
    path[0] = 0;

    tspBacktrackingAux(path, 1, 0);

    memcpy(path, minPath, sizeof(unsigned int)*vertexSet.size());
    delete minPath;
    return minCost;
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

vector<Edge*> Graph::NearestPointsPath() {
    cout <<"Starting Priority Queues\n";
    vector<priority_queue<Edge*, vector<Edge*>, comp>> vertices;
    vertices.reserve(vertexSet.size());
    for(Vertex* v : vertexSet){
        priority_queue<Edge*, vector<Edge*>, comp> vpq;
        for(Edge* e : v->getAdj()){
            vpq.push(e);
        }
        vertices.push_back(vpq);
    }
    cout << "Done Priority Queues\n";

    cout << "Starting NearestPointsPath\n";
    vector<Edge*> path;
    unsigned long cost = ULONG_MAX;
    for(int i; i < vertexSet.size(); i++){
//        cout << "i = " << i << endl;
        vector<Edge*> path2 = NearestPointsPath(i, vertices);
        unsigned long cost2 = 0;
        for(Edge* e : path2)
            cost2 += e->getDist();
        if(cost2 < cost){
            cost = cost2;
            path = path2;
        }
    }
    cout << "Done NearestPointsPath\n";
    return path;
}

vector<Edge*> Graph::NearestPointsPath(int start, vector<priority_queue<Edge*, vector<Edge*>, comp>> vertices){
    vector<Edge*> path;
    unordered_set<int> visited;
    visited.insert(start);

    path.clear();
    int n = vertexSet.size();
    int i = 0;
    Vertex* curr = vertexSet[start];
    while (i < n - 1) {
        priority_queue<Edge *, vector<Edge *>, comp> adj = vertices[curr->getId()];
        if(adj.empty())
            return vector<Edge*>();

        while(visited.find(adj.top()->getDest()->getId()) != visited.end()){
            adj.pop();
            if(adj.empty())
                return vector<Edge*>();
        }

        Edge* e = adj.top();
        adj.pop();
        visited.insert(e->getDest()->getId());
        path.push_back(e);
        curr = e->getDest();
        i++;
    }

    Edge *e = get_edge(*this, path.back()->getDest()->getId(), 0);
    if (e != nullptr)
        path.push_back(e);
    else {
        cout << "Path failed\n";
        return vector<Edge *>();
    }
    return path;
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
                cout << "Poping " << curr << endl;
            }
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
//            cout << "Creating edge\n";
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
