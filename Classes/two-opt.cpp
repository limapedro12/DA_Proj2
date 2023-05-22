#include "two-opt.h"

using namespace std;

int pathLengthSq(vector<Edge*> &path) {
    int length = 0;
    for (int i = 0; i < path.size(); i++) {
        length += path[i]->getDist()*path[i]->getDist();
    }
    return length;
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

bool do2OptAll(vector<int> &path, int i, int j) {
    // Reverse path[i+1] to path[j]
    for(int k = 0; k < (j-i)/2; k++){
        int temp = path[i+1+k];
        path[i+1+k] = path[j-k];
        path[j-k] = temp;
    }

    return true;
}

double dist2(const Vertex* v1, const Vertex* v2) {
    double h = haversine(v1->getLat(), v1->getLon(), v2->getLat(), v2->getLon());
    return h*h;
}

void vIntToVEdge(vector<int> &path, vector<Edge*> &path2, Graph g){
    for(int i = 0; i < path.size()-1; i++){
        Edge* e = get_edge(g, path[i], path[(i+1) % path.size()]);
        if(e == nullptr)
            e = new Edge(g.findVertex(path[i]), g.findVertex(path[i+1]),
                         haversine(g.findVertex(path[i])->getLat(),
                                       g.findVertex(path[i])->getLon(),
                                       g.findVertex(path[i+1])->getLat(),
                                       g.findVertex(path[i+1])->getLon()));
        path2[i] = e;
    }
}

// Print the path.
void printPath(string pathName, vector<Edge*> &path) {
    cout << pathName << " = [";
    for (int i = 0; i < path.size(); i++) {
//        if (i % 10 == 0) {
//            cout << "\n    ";
//        }
        cout << path[i]->getSource()->getId() << ", ";
    }
    cout << path.back()->getDest()->getId() << "];\n";
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

    auto e1 = adj[0].begin();
    auto end1 = adj[0].end();
    auto e2 = adj[0].begin();
    auto end2 = adj[0].end();
    double lengthDelta;
    while (foundImprovement) {
        foundImprovement = false;
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                e1 = adj[path[i]->getSource()->getId()].find(path[j]->getSource()->getId());
                end1 = adj[path[i]->getSource()->getId()].end();
                e2 = adj[path[i]->getDest()->getId()].find(path[j]->getDest()->getId());
                end2 = adj[path[i]->getDest()->getId()].end();
                if(e1 == end1 || e2 == end2)
                    continue;

                lengthDelta = -path[i]->getDist() - path[j]->getDist() + e2->second + e1->second;
                lengthDelta = round(lengthDelta*100)/100;

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
    cout << "Done 2-opt\n";
    return path;
}

vector<Edge*> improvePathAll(vector<Edge*> path, Graph g){
    double curLength = pathLengthSq(path);
    int n = path.size();
    bool foundImprovement = true;
    cout << "Starting 2-opt\n";

    vector<int> path_temp;
    for(int i = 0; i < n; i++){
        path_temp.push_back(path[i]->getSource()->getId());
    }

    double lengthDelta;
    while (foundImprovement) {
        foundImprovement = false;
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {

                int v1 = path_temp[i];
                int v2 = path_temp[(i+1) % n];
                int v3 = path_temp[j];
                int v4 = path_temp[(j+1) % n];
                lengthDelta = - dist2(g.findVertex(v1), g.findVertex(v2))
                              - dist2(g.findVertex(v3), g.findVertex(v4))
                              + dist2(g.findVertex(v1), g.findVertex(v3))
                              + dist2(g.findVertex(v2), g.findVertex(v4));

                lengthDelta = round(lengthDelta*100)/100;

                // If the length of the path is reduced, do a 2-opt swap
                if (lengthDelta < 0) {
                    do2OptAll(path_temp, i, j);
                    curLength += lengthDelta;
                    foundImprovement = true;
                }
            }
        }
    }
    vIntToVEdge(path_temp, path, g);
    cout << "Done 2-opt\n";
    return path;
}

