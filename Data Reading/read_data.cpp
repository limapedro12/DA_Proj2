#include "read_data.h"

void readToy(const std::string& filename, Graph& g) {
    g.clear();

    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);

    while(std::getline(file, line)) {
        std::string src, dest, dist;
        std::istringstream iss(line);
        std::getline(iss, src, ',');
        std::getline(iss, dest, ',');
        std::getline(iss, dist, ',');

        int source = stoi(src);
        int destination = stoi(dest);
        double distance = stod(dist);

        Vertex* s = g.findVertex(source);
        Vertex* d = g.findVertex(destination);

        if (s == nullptr) {
            s = new Vertex(source);
            g.addVertex(s);
        }

        if (d == nullptr) {
            d = new Vertex(destination);
            g.addVertex(d);
        }

        g.addBidirectionalEdge(s, d, distance);
    }
}
