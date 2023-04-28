#ifndef DA_PROJ2_VERTEXEDGE_H
#define DA_PROJ2_VERTEXEDGE_H

#include <string>

class Edge;

class Vertex {
public:
    Vertex(int id);
    Vertex(int id, double lat, double lon);
    int getId() const;
private:
    int id;
    double lat = 0;
    double lon = 0;
};

class Edge{};

#endif //DA_PROJ2_VERTEXEDGE_H
