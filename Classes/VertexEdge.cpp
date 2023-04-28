#include "VertexEdge.h"

Vertex::Vertex(int id) {
    this->id = id;
}

Vertex::Vertex(int id, double lat, double lon) {
    this->id = id;
    this->lat = lat;
    this->lon = lon;
}

int Vertex::getId() const {
    return id;
}
