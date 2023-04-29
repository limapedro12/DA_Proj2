#include "read_data.h"

void readToy(const std::string& filename, Graph& g) {
    g.clear();

    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);

    std::cout << "Loading...\n\n";

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

void readReal(int graph_no, Graph& g) {
    g.clear();

    std::ifstream nodes("../Project2Data/Real-World-Graphs/graph" + std::to_string(graph_no) + "/nodes.csv");
    std::ifstream edges("../Project2Data/Real-World-Graphs/graph" + std::to_string(graph_no) + "/edges.csv");

    std::string line;
    std::getline(nodes, line);

    std::cout << "Loading...\n\n";

    while (std::getline(nodes, line)) {
        std::string id_string, lon_string, lat_string;
        std::istringstream iss(line);
        std::getline(iss, id_string, ',');
        std::getline(iss, lon_string, ',');
        std::getline(iss, lat_string, ',');

        int id = stoi(id_string);
        double lat = stod(lat_string);
        double lon = stod(lon_string);

        Vertex* v = new Vertex(id, lat, lon);
        g.addVertex(v);
    }

    std::getline(edges, line);

    while (std::getline(edges, line)) {
        std::string source_string, dest_string, dist_string;
        std::istringstream iss(line);
        std::getline(iss, source_string, ',');
        std::getline(iss, dest_string, ',');
        std::getline(iss, dist_string, ',');

        int source_id = stoi(source_string);
        int dest_id = stoi(dest_string);
        double dist = stod(dist_string);

        Vertex* source = g.findVertex(source_id);
        Vertex* dest = g.findVertex(dest_id);

        g.addBidirectionalEdge(source, dest, dist);
    }
}
