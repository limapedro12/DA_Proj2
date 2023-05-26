#include <vector>

using namespace std;

struct perm{
    int number;
    bool is_reverse;
};

vector<vector<perm>> comb = {
        {{1, 0},{2, 1},{0, 0}},
        {{2, 0},{1, 1},{0, 1}},
        ...
}

int doKopt(vector<Edge*> path, vector<int> edgesToSwap, int vector<unordered_map<int, double>> adj){
    vector<Edge*> newPath = path;
    int lenghtDelta = 0;
    for(int e : edgesToSwap){
        lenghtDelta -= path[e]->getDist();
    for(auto vc : comb){
        int tempDelta = lenghtDelta;
        for(int i = 0; i < vc.size(); i++) {
            int c = vc[i].number;
            tempDelta += adj[newPath[edgesToSwap[c]-1]->getDest()->getId()][newPath[edgesToSwap[c+1]+1]->getSource()->getId()];
        }
        if(tempDelta > 0)
            continue
        for(int i = 0; i < vc.size(); i++){
            int c = vc[i].number;
            if(vc[i].is_reverse){
                reverse in path edgesToSwap[c]+1 to edgesToSwap[c+1];
            }
//            copy edgesToSwap[c]+1 to edgesToSwap[c+1] to newPath[edgesToSwap[i]+1];
            copy(path.begin()+edgesToSwap[c]+1, path.begin()+edgesToSwap[c+1], newPath.begin()+edgesToSwap[i]+1);
            newPath[edgesToSwap[c]] = getEdge(newPath[edgesToSwap[c]-1]->getDest(), newPath[edgesToSwap[c]+1]->getSource());
        }
        newPath[edgesToSwap.back()] = getEdge(newPath[edgesToSwap.back() - 1]->getDest(), newPath[edgesToSwap.back() + 1]->getSource());
        path = newPath;
    }
}

