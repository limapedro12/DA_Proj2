#include "read_data.h"

void readToy(const std::string& name, Graph& g) {
    g.clear();

    std::ifstream nodes("../Project2Data/Toy-Graphs/" + name + "/nodes.csv");
    std::ifstream edges("../Project2Data/Toy-Graphs/" + name + "/edges.csv");

    std::string line;
    std::getline(nodes, line);

    std::cout << "A carregar...\n\n";

    while(std::getline(nodes, line)) {
        unsigned int id = stoul(line);

        Vertex* v = new Vertex(id);
        g.addVertex(v);
    }

    std::getline(edges, line);

    while (std::getline(edges, line)) {
        std::string source_string, dest_string, dist_string;
        std::istringstream iss(line);
        std::getline(iss, source_string, ',');
        std::getline(iss, dest_string, ',');
        std::getline(iss, dist_string, ',');

        unsigned int source_id = stoul(source_string);
        unsigned int dest_id = stoul(dest_string);
        double dist = stod(dist_string);

        Vertex* source = g.findVertex(source_id);
        Vertex* dest = g.findVertex(dest_id);

        g.addBidirectionalEdge(source, dest, dist);
    }

}

void readReal(int graph_no, Graph& g) {
    g.clear();

    std::ifstream nodes("../Project2Data/Real-World-Graphs/graph" + std::to_string(graph_no) + "/nodes.csv");
    std::ifstream edges("../Project2Data/Real-World-Graphs/graph" + std::to_string(graph_no) + "/edges.csv");

    std::string line;
    std::getline(nodes, line);

    std::cout << "A carregar...\n\n";

    while (std::getline(nodes, line)) {
        std::string id_string, lon_string, lat_string;
        std::istringstream iss(line);
        std::getline(iss, id_string, ',');
        std::getline(iss, lon_string, ',');
        std::getline(iss, lat_string, ',');

        unsigned int id = stoul(id_string);
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

        unsigned int source_id = stoul(source_string);
        unsigned int dest_id = stoul(dest_string);
        double dist = stod(dist_string);

        Vertex* source = g.findVertex(source_id);
        Vertex* dest = g.findVertex(dest_id);

        g.addBidirectionalEdge(source, dest, dist);
    }

    g.hasCoord = true;
}

void readExtra(unsigned int node_count, Graph& g) {
    for (unsigned int i = 0; i < node_count; i++) g.addVertex(new Vertex(i));

    std::ifstream edges("../Project2Data/Extra-Fully-Connected-Graphs/edges_" + std::to_string(node_count) + ".csv");

    std::string line;

    while (std::getline(edges, line)) {
        std::string source_string, dest_string, dist_string;
        std::istringstream iss(line);
        std::getline(iss, source_string, ',');
        std::getline(iss, dest_string, ',');
        std::getline(iss, dist_string, ',');

        unsigned int source_id = stoul(source_string);
        unsigned int dest_id = stoul(dest_string);
        double dist = stod(dist_string);

        Vertex* source = g.findVertex(source_id);
        Vertex* dest = g.findVertex(dest_id);

        g.addBidirectionalEdge(source, dest, dist);
    }
}
