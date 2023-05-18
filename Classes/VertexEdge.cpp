#include "VertexEdge.h"

Vertex::Vertex(unsigned int id) {
    this->id = id;
}

Vertex::Vertex(unsigned int id, double lat, double lon) {
    this->id = id;
    this->lat = lat;
    this->lon = lon;
}

unsigned int Vertex::getId() const {
    return id;
}

double Vertex::getLat() const {
    return lat;
}

double Vertex::getLon() const {
    return lon;
}

std::vector<Edge*> Vertex::getAdj() const {
    return adj;
}

Edge* Vertex::addEdge(Vertex *dest, double dist) {
    Edge* e = new Edge(this, dest, dist);
    adj.push_back(e);
    return e;
}

void Vertex::print() const {
    std::cout << id << std::endl;
    for (Edge* e : adj) e->print();
    std::cout << std::endl;
}

Edge::Edge(Vertex *source, Vertex *dest, double dist) {
    this->source = source;
    this->dest = dest;
    this->dist = dist;
}

Vertex* Edge::getSource() const {
    return source;
}

Vertex* Edge::getDest() const {
    return dest;
}

double Edge::getDist() const {
    return dist;
}

Edge* Edge::getReverse() const {
    return reverse;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::print() const {
    std::cout << "->" << dest->getId() << ',' << dist << std::endl;
}


