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

template <typename T>
bool do2Opt2(list<int> &path, T i, T j) {
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
//        cout << "More 2-opt\n";
        foundImprovement = false;
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
//                auto e1 = get_edge(path[i]->getSource(), path[j]->getSource());
                e1 = adj[path[i]->getSource()->getId()].find(path[j]->getSource()->getId());
                end1 = adj[path[i]->getSource()->getId()].end();
//                auto e2 = get_edge(path[i]->getDest(), path[j]->getDest());
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

vector<Edge*> improvePath2(vector<Edge*> path, Graph g){
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

    list<int> list_path;
    for(int i = 0; i < n; i++){
        list_path.push_back(path[i]->getSource()->getId());
    }

    auto e1 = adj[0].begin();
    auto end1 = adj[0].end();
    auto e2 = adj[0].begin();
    auto end2 = adj[0].end();
    double lengthDelta;
    while (foundImprovement) {
//        cout << "More 2-opt\n";
        foundImprovement = false;
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
//                auto e1 = get_edge(path[i]->getSource(), path[j]->getSource());
                e1 = adj[path[i]->getSource()->getId()].find(path[j]->getSource()->getId());
                end1 = adj[path[i]->getSource()->getId()].end();
//                auto e2 = get_edge(path[i]->getDest(), path[j]->getDest());
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

