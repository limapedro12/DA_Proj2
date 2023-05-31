#ifndef DA_PROJ2_VERTEXEDGE_H
#define DA_PROJ2_VERTEXEDGE_H

#include <string>
#include <vector>

#include <iostream>

class Edge;

/**
 * @brief Represents a graph's vertex.
 *
 * Represents a graph's vertex/node by its id (for some graphs of the given
 * dataset, latitude and longitude) and their adjacent edges.
 *
 * NOTE: The terms "vertex" and "node" ara use interchangeably.
 */
class Vertex {
public:
    /**
     * Vertex basic constructor.
     *
     * @param id Id of the vertex to be created
     */
    Vertex(unsigned int id);

    /**
     * Vertex constructor.
     *
     * @param id Id of the vertex to be created
     * @param lat Latitude of the vertex to be created
     * @param lon Longitude of the vertex to be created
     */
    Vertex(unsigned int id, double lat, double lon);

    /**
     * Vertex's id getter.
     *
     * @return Vertex's id
     */
    unsigned int getId() const;

    /**
     * Vertex's latitude getter.
     *
     * @return Vertex's latitude
     */
    double getLat() const;

    /**
     * Veretx's longitude getter.
     *
     * @return Vertex's longitude
     */
    double getLon() const;

    /**
     * Getter of vertex's (pointers to) adjacent edges set.
     *
     * @return A copy of the vertex's vector of (pointers to) adjacent edges.
     */
    std::vector<Edge*> getAdj() const;

    /**
     * Adds and returns a pointer to an Edge to the vertex's (pointers to) adjacent edges.
     *
     * @param dest Pointer to the destination vertex
     * @param dist Distance of the edge to be created
     * @return Pointer to the created edge
     */
    Edge* addEdge(Vertex* dest, double dist);

    /**
     * Prints vertex's information.
     */
    void print() const;
private:
    unsigned int id;
    double lat = 0;
    double lon = 0;
    std::vector<Edge*> adj;
};

/**
 * @brief Represents an edge between two vertexes/nodes of a graph.
 *
 * Represents an edge between to nodes of a graph by pointers to the two ends and distance.
 *
 * NOTE: The terms "vertex" and "node" are used interchangeably.
 */
class Edge{
public:
    /**
     * Edge constructor.
     * @param source Pointer to the source Vertex
     * @param dest Pinter to the destination Vertex
     * @param dist Distance of the edge to be constructed
     */
    Edge(Vertex* source, Vertex* dest, double dist);

    /**
     * Source Vertex getter.
     *
     * @return Pointer to the edge's source Vertex.
     */
    Vertex* getSource() const;

    /**
     * Destination Vertex getter.
     *
     * @return Pointer to the edge's destination Vertex.
     */
    Vertex* getDest() const;

    /**
     * Edge's distance getter.
     *
     * @return The edge's size (distance)
     */
    double getDist() const;

    /**
     * Getter of the reverse edge (source and destination switched).
     *
     * @return Pointer to the reverse edge
     */
    Edge* getReverse() const;

    /**
     * Reverse edge setter.
     *
     * @param reverse Pointer to the edge to be set as instance's reverse.
     */
    void setReverse(Edge* reverse);

    /**
     * Prints information about the edge.
     */
    void print() const;
private:
    Vertex* source;
    Vertex* dest;
    double dist;
    Edge* reverse = nullptr;
};

#endif //DA_PROJ2_VERTEXEDGE_H
