#include "two-opt.h"

using namespace std;

void reverse(vector<Edge*> &path, int i, int j){
    // Reverse path[i] to path[j-1]
   for(int k = 0; k < (j-i+1)/2; k++){
       Edge* temp = path[i+k];
       path[i+k] = path[j-1-k]->getReverse();
       path[j-1-k] = temp->getReverse();
   }
}

void copy(vector<Edge*> &path, vector<Edge*> &newPath, int startPath, int endPath, int startNewPath){
    copy(path.begin() + startPath, path.begin() + endPath, newPath.begin() + startNewPath);
}

int verify3Opt(vector<Edge*> &path, int i, int j, int k, vector<vector<Edge*>> adj) {
    if(i >= j || j >= k || i < 0 || k >= path.size()) {
        return -1;
    }
    
    double currentEdgeLength = path[i]->getDist() + path[j]->getDist() + path[k]->getDist();
    currentEdgeLength = ::round(currentEdgeLength*100)/100;
    double minDelta = currentEdgeLength;
    int selectedPath = 0;
    int iSource = path[i]->getSource()->getId();
    int iDest = path[i]->getDest()->getId();
    int jSource = path[j]->getSource()->getId();
    int jDest = path[j]->getDest()->getId();
    int kSource = path[k]->getSource()->getId();
    int kDest = path[k]->getDest()->getId();
//    if (adj[iSource].find[jSource] != adj[iSource].end() && adj[jDest].find(iDest) != adj[jDest].end()) {
    if (adj[iSource][jSource] != nullptr && adj[jDest][iDest] != nullptr) {
        double delta = path[k]->getDist() + adj[iSource][jSource]->getDist() + adj[iDest][jDest]->getDist();
        delta = ::round(delta*100)/100;
        if (delta < minDelta) {
            minDelta = delta;
            selectedPath = 1;
        }
    }
//    if (adj[iSource].find(kSource) != adj[iSource].end() && adj[kDest].find(iDest) != adj[kDest].end()) {
    if (adj[iSource][kSource] != nullptr && adj[kDest][iDest] != nullptr) {
        double delta = path[j]->getDist() + adj[iSource][kSource]->getDist() + adj[iDest][kDest]->getDist();
        delta = ::round(delta*100)/100;
        if (delta < minDelta) {
            minDelta = delta;
            selectedPath = 2;
        }
    }
//    if (adj[jSource].find(kSource) != adj[jSource].end() && adj[kDest].find(jDest) != adj[kDest].end()) {
    if (adj[jSource][kSource] != nullptr && adj[kDest][jDest] != nullptr) {
        double delta = path[i]->getDist() + adj[jSource][kSource]->getDist() + adj[jDest][kDest]->getDist();
        delta = ::round(delta*100)/100;
        if (delta < minDelta) {
            minDelta = delta;
            selectedPath = 3;
        }
    }
//    if (adj[iSource].find(jDest) != adj[iSource].end() &&
//        adj[jSource].find(kDest) != adj[jSource].end() &&
//        adj[kSource].find(iDest) != adj[kSource].end()) {
    if (adj[iSource][jDest] != nullptr &&
        adj[jSource][kDest] != nullptr &&
        adj[kSource][iDest] != nullptr) {
        double delta = adj[iSource][jDest]->getDist() + adj[jSource][kDest]->getDist() + adj[kSource][iDest]->getDist();
        delta = ::round(delta*100)/100;
        if (delta < minDelta) {
            minDelta = delta;
            selectedPath = 4;
        }
    }
//    if (adj[iSource].find(jSource) != adj[iSource].end() &&
//        adj[iDest].find(kSource) != adj[iDest].end() &&
//        adj[jDest].find(kDest) != adj[jDest].end()) {
    if (adj[iSource][jSource] != nullptr &&
        adj[iDest][kSource] != nullptr &&
        adj[jDest][kDest] != nullptr) {
        double delta = adj[iSource][jSource]->getDist() + adj[iDest][kSource]->getDist() + adj[jDest][kDest]->getDist();
        delta = ::round(delta*100)/100;
        if (delta < minDelta) {
            minDelta = delta;
            selectedPath = 5;
        }
    }
//    if (adj[iSource].find(jDest) != adj[iSource].end() &&
//        adj[kSource].find(jSource) != adj[kSource].end() &&
//        adj[iDest].find(kDest) != adj[iDest].end()) {
    if (adj[iSource][jDest] != nullptr &&
        adj[kSource][jSource] != nullptr &&
        adj[iDest][kDest] != nullptr) {
        double delta = adj[iSource][jDest]->getDist() + adj[kSource][jSource]->getDist() + adj[iDest][kDest]->getDist();
        delta = ::round(delta*100)/100;
        if (delta < minDelta) {
            minDelta = delta;
            selectedPath = 6;
        }
    }
//    if (adj[iSource].find(kSource) != adj[iSource].end() &&
//        adj[jDest].find(iDest) != adj[jDest].end() &&
//        adj[jSource].find(kDest) != adj[jSource].end()) {
    if (adj[iSource][kSource] != nullptr &&
        adj[jDest][iDest] != nullptr &&
        adj[jSource][kDest] != nullptr) {
        double delta = adj[iSource][kSource]->getDist() + adj[jDest][iDest]->getDist() + adj[jSource][kDest]->getDist();
        delta = ::round(delta*100)/100;
        if (delta < minDelta) {
            minDelta = delta;
            selectedPath = 7;
        }
    }
    return selectedPath;
}

bool do3Opt(vector<Edge*> &path, int i, int j, int k, int selectedPath, vector<vector<Edge*>> adj) {
    if(i >= j || j >= k || i < 0 || k >= path.size()) {
        return false;
    }
    
    int iSource = path[i]->getSource()->getId();
    Vertex* iSourceVertex = path[i]->getSource();
    int iDest = path[i]->getDest()->getId();
    Vertex* iDestVertex = path[i]->getDest();
    int jSource = path[j]->getSource()->getId();
    Vertex* jSourceVertex = path[j]->getSource();
    int jDest = path[j]->getDest()->getId();
    Vertex* jDestVertex = path[j]->getDest();
    int kSource = path[k]->getSource()->getId();
    Vertex* kSourceVertex = path[k]->getSource();
    int kDest = path[k]->getDest()->getId();
    Vertex* kDestVertex = path[k]->getDest();

    vector<Edge*> newPath = path;

    switch (selectedPath) {
        case 1:
//            newPath[i] = get_edge(iSourceVertex, jSourceVertex);
            newPath[i] = adj[iSource][jSource];
//            newPath[j] = get_edge(iDestVertex, jDestVertex);
            newPath[j] = adj[iDest][jDest];
            reverse(newPath, i+1, j);
            break;
        case 2:
//            newPath[i] = get_edge(iSourceVertex, kSourceVertex);
            newPath[i] = adj[iSource][kSource];
//            newPath[k] = get_edge(iDestVertex, kDestVertex);
            newPath[k] = adj[iDest][kDest];
            reverse(newPath, i+1, k);
            break;
        case 3:
//            newPath[j] = get_edge(jSourceVertex, kSourceVertex);
            newPath[j] = adj[jSource][kSource];
//            newPath[k] = get_edge(jDestVertex, kDestVertex);
            newPath[k] = adj[jDest][kDest];
            reverse(newPath, j+1, k);
            break;
        case 4: 
//            newPath[i] = get_edge(iSourceVertex, jDestVertex);
            newPath[i] = adj[iSource][jDest];
            copy(path, newPath, j+1, k, i+1);
//            newPath[i+k-j] = get_edge(kSourceVertex, iDestVertex);
            newPath[i+k-j] = adj[kSource][iDest];
            copy(path, newPath, i+1, j, i+k-j+1);
//            newPath[k] = get_edge(jSourceVertex, kDestVertex);
            newPath[k] = adj[jSource][kDest];
            break;
        case 5:
//            newPath[i] = get_edge(iSourceVertex, jSourceVertex);
            newPath[i] = adj[iSource][jSource];
            reverse(newPath, i+1, j);
//            newPath[j] = get_edge(iDestVertex, kSourceVertex);
            newPath[j] = adj[iDest][kSource];
            reverse(newPath, j+1, k);
//            newPath[k] = get_edge(jDestVertex, kDestVertex);
            newPath[k] = adj[jDest][kDest];
            break;
        case 6:
//            newPath[i] = get_edge(iSourceVertex, jDestVertex);
            newPath[i] = adj[iSource][jDest];
            copy(path, newPath, j+1, k, i+1);
//            newPath[i+k-j] = get_edge(kSourceVertex, jSourceVertex);
            newPath[i+k-j] = adj[kSource][jSource];
            copy(path, newPath, i+1, j, i+k-j+1);
            reverse(newPath, i+k-j+1, k);
//            newPath[k] = get_edge(iDestVertex, kDestVertex);
            newPath[k] = adj[iDest][kDest];
            break;
        case 7:
//            newPath[i] = get_edge(iSourceVertex, kSourceVertex);
            newPath[i] = adj[iSource][kSource];
            copy(path, newPath, j+1, k, i+1);
            reverse(newPath, i+1, i+k-j);
//            newPath[i+k-j] = get_edge(jDestVertex, iDestVertex);
            newPath[i+k-j] = adj[jDest][iDest];
            copy(path, newPath, i+1, j, i+k-j+1);
//            newPath[k] = get_edge(jSourceVertex, kDestVertex);
            newPath[k] = adj[jSource][kDest];
            break;
        default:
            return false;
    }
    for(int x = 0; x < path.size()-1; x++) {
        if(newPath[x]->getDest()->getId() != newPath[x+1]->getSource()->getId())
            return false;
    }
    if(newPath[0]->getSource()->getId() != 0 || newPath[newPath.size()-1]->getDest()->getId() != 0)
        return false;
    path = newPath;
    return true;
//    Edge* e_first = get_edge(path[i]->getSource(), path[j]->getSource());
//    Edge* e_last = get_edge(path[i]->getDest(), path[j]->getDest());
//    if(e_first == nullptr || e_last == nullptr)
//        return false;
//
//    // Reverse path[i+1] to path[j]
//    for(int k = 0; k < (j-i)/2; k++){
//        Edge* temp = path[i+1+k];
//        path[i+1+k] = path[j-1-k]->getReverse();
//        path[j-1-k] = temp->getReverse();
//    }
//    path[i] = e_first;
//    path[j] = e_last;
//    return true;
}

//double dist2(const Vertex* v1, const Vertex* v2) {
//    double h = haversine(v1->getLat(), v1->getLon(), v2->getLat(), v2->getLon());
//    return h*h;
//}

unsigned long combinations(unsigned n, unsigned k){
    if (k > n)
        return 0;
    if (k * 2 > n) 
        k = n-k;
    if (k == 0) 
        return 1;

    unsigned long result = n;
    for( int i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

vector<bool> done_percentages = vector<bool>(10, false);
void printProgress(double proportion){
    int percent = (int) (proportion*100);
    if(!done_percentages[percent/10]){
        cout << percent << "%\n";
        done_percentages[percent/10] = true;
    }
}

vector<Edge*> improvePath3Opt(vector<Edge*> path, Graph g){
    // double curLength = pathLengthSq(path);
    cout << "Starting 3-opt\n";
    done_percentages = vector<bool>(10, false);
    unsigned long number_of_combinations = combinations(path.size(), 3);
    path = improvePath(path, g, false);
    bool foundImprovement = true;
    int n = path.size();
//    vector<unordered_map<int, double>> adj(n);
    vector<vector<Edge*>> adj(n, vector<Edge*>(n, nullptr));
    for(int i = 0; i < n; i++){
        for(Edge* e: g.getVertexSet()[i]->getAdj()){
//            adj[i].insert({e->getDest()->getId(), e->getDist()});
            adj[i][e->getDest()->getId()] = e;
        }
    }

//    while (foundImprovement) {
        foundImprovement = false;
        std::string bitmask(3, 1); // K leading 1's
        bitmask.resize(path.size(), 0); // N-K trailing 0's

        vector<int> selectedNums;
        selectedNums.reserve(3);
        int count = 0;
    
        // print integers and permute bitmask
        do {
            selectedNums.clear();
            for (int i = 0; i < path.size(); ++i) // [0..N-1] integers
            {
                if (bitmask[i]) {
                    selectedNums.push_back(i);
                }
            }
            if(selectedNums[0] + 1 == selectedNums[1] || selectedNums[1] + 1 == selectedNums[2])
                continue;
            int selectedPath = verify3Opt(path, selectedNums[0], selectedNums[1], selectedNums[2], adj);
            if(selectedPath > 0 && selectedPath < 8){
//                foundImprovement = true;
                do3Opt(path, selectedNums[0], selectedNums[1], selectedNums[2], selectedPath, adj);
//                double curLength = pathLengthSq(path);
//                cout << "Found improvement: " << curLength << " - " << selectedPath << endl;
            }
            count++;
            printProgress((double)count/number_of_combinations);
        } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
//    }
//    for(int i = 0; i < path.size(); i++){
//        cout << path[i]->getSource()->getId() << "->" << path[i]->getDest()->getId() << endl;
//    }
    cout << "Done 3-opt\n";
    return path;
    // double curLength = pathLengthSq(path);
    // int n = path.size();
    // bool foundImprovement = true;
    // cout << "Starting 2-opt\n";
    // vector<unordered_map<int, double>> adj(n);
    // for(int i = 0; i < n; i++){
    //     for(Edge* e: g.getVertexSet()[i]->getAdj()){
    //         adj[i].insert({e->getDest()->getId(), e->getDist()});
    //     }
    // }

    // auto e1 = adj[0].begin();
    // auto end1 = adj[0].end();
    // auto e2 = adj[0].begin();
    // auto end2 = adj[0].end();
    // double lengthDelta;
    // while (foundImprovement) {
    //     foundImprovement = false;
    //     for (int i = 0; i < n - 2; i++) {
    //         for (int j = i + 1; j < n - 1; j++) {
    //             e1 = adj[path[i]->getSource()->getId()].find(path[j]->getSource()->getId());
    //             end1 = adj[path[i]->getSource()->getId()].end();
    //             e2 = adj[path[i]->getDest()->getId()].find(path[j]->getDest()->getId());
    //             end2 = adj[path[i]->getDest()->getId()].end();
    //             if(e1 == end1 || e2 == end2)
    //                 continue;

    //             lengthDelta = -path[i]->getDist() - path[j]->getDist() + e2->second + e1->second;
    //             lengthDelta = round(lengthDelta*100)/100;

    //             // If the length of the path is reduced, do a 2-opt swap
    //             if (lengthDelta < 0) {
    //                 if(!do2Opt(path, i, j))
    //                     continue;
    //                 curLength += lengthDelta;
    //                 foundImprovement = true;
    //             }
    //         }
    //     }
    // }
    // cout << "Done 2-opt\n";
    // return path;
}

vector<Edge*> improvePathAll3Opt(vector<Edge*> path, Graph g){
    // double curLength = pathLengthSq(path);
    cout << "Starting 3-opt\n";
    path = improvePathAll(path, g, false);
    bool foundImprovement = true;
    int n = path.size();
//    vector<unordered_map<int, double>> adj(n);
    vector<vector<Edge*>> adj(n, vector<Edge*>(n, nullptr));
    for(int i = 0; i < n; i++){
        for(Edge* e: g.getVertexSet()[i]->getAdj()){
//            adj[i].insert({e->getDest()->getId(), e->getDist()});
            adj[i][e->getDest()->getId()] = e;
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(adj[i][j] != nullptr) {
                Edge* e = new Edge(g.getVertexSet()[i], g.getVertexSet()[j], haversine(g.getVertexSet()[i]->getLat(),
                                                                                                  g.getVertexSet()[i]->getLon(),
                                                                                                  g.getVertexSet()[j]->getLat(),
                                                                                                  g.getVertexSet()[j]->getLon()));
                Edge *e_reverse = new Edge(g.getVertexSet()[j], g.getVertexSet()[i], e->getDist());
                e->setReverse(e_reverse);
                e_reverse->setReverse(e);
                adj[j][i] = e_reverse;
            }
        }
    }

    while (foundImprovement) {
        foundImprovement = false;
        std::string bitmask(3, 1); // K leading 1's
        bitmask.resize(path.size(), 0); // N-K trailing 0's

        vector<int> selectedNums;
        selectedNums.reserve(3);

        // print integers and permute bitmask
        do {
            selectedNums.clear();
            for (int i = 0; i < path.size(); ++i) // [0..N-1] integers
            {
                if (bitmask[i]) {
                    selectedNums.push_back(i);
                }
            }
            if(selectedNums[0] + 1 == selectedNums[1] || selectedNums[1] + 1 == selectedNums[2])
                continue;
            int selectedPath = verify3Opt(path, selectedNums[0], selectedNums[1], selectedNums[2], adj);
            if(selectedPath > 0 && selectedPath < 8){
                foundImprovement = true;
                do3Opt(path, selectedNums[0], selectedNums[1], selectedNums[2], selectedPath, adj);
//                double curLength = pathLengthSq(path);
//                cout << "Found improvement: " << curLength << " - " << selectedPath << endl;
            }
        } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    }
//    for(int i = 0; i < path.size(); i++){
//        cout << path[i]->getSource()->getId() << "->" << path[i]->getDest()->getId() << endl;
//    }
    cout << "Done 3-opt\n";
    return path;
}

