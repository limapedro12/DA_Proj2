#include "read_data.h"

void readToy(const std::string& filename, Graph& g) {
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
        int distance = stoi(dist);

        Vertex* s = g.findVertex(source);
        Vertex* d = g.findVertex(destination);

        if (s == nullptr) s = new Vertex(source);

        if (d == nullptr) d = new Vertex(destination);

        // CREATE AND ADD EDGES
    }
}
