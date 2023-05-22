#ifndef DA_PROJ2_VERTEXEDGE_H
#define DA_PROJ2_VERTEXEDGE_H

#include <string>
#include <vector>

#include <iostream>

class Edge;

class Vertex {
public:
    Vertex(unsigned int id);
    Vertex(unsigned int id, double lat, double lon);
    unsigned int getId() const;
    double getLat() const;
    double getLon() const;
    std::vector<Edge*> getAdj() const;
    Edge* addEdge(Vertex* dest, double dist);

    void print() const;
private:
    unsigned int id;
    double lat = 0;
    double lon = 0;
    std::vector<Edge*> adj;
};

class Edge{
public:
    Edge(Vertex* source, Vertex* dest, double dist);
    Vertex* getSource() const;
    Vertex* getDest() const;
    double getDist() const;
    Edge* getReverse() const;
    void setReverse(Edge* reverse);

    void print() const;
private:
    Vertex* source;
    Vertex* dest;
    double dist;
    Edge* reverse = nullptr;
};

#endif //DA_PROJ2_VERTEXEDGE_H
