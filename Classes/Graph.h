#ifndef DA_PROJ2_GRAPH_H
#define DA_PROJ2_GRAPH_H

#include "VertexEdge.h"

#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <random>
#include <cstdio>
#include <vector>

struct comp { bool operator()(Edge* e1, Edge* e2){
        return e1->getDist() < e2->getDist();
    }};

/**
 * @brief A class that represents a graph.
 *
 * The Graph class is the most important class of the program, since it models the dataset
 * that the developed tasks/algorithms will run on.\n
 * Each instance contains all its nodes/vertexes organized in a vector, each one of the nodes
 * containing the respective edges.
 *
 * NOTE: The terms "node" and "vertex" are used interchangeably.
 */
class Graph {
public:
    /**
     * Finds and returns a pointer to a vertex in the graph's vertex set.
     *
     * Time complexity: O(1).
     *
     * @param id Id of the vertex whose pointer is to be returned
     * @return Pointer to the vertex with the given id, nullptr if not found.
     */
    Vertex* findVertex(unsigned int id) const;

    /**
     * Graph's vertex set getter.
     *
     * @return A copy of the vector of pointers to the graph's nodes.
     */
    std::vector<Vertex*> getVertexSet() const;

    /**
     * Getter of the graph's number of nodes.
     *
     * @return The count of graph's nodes.
     */
    int getNumVertex() const;

    /**
     * Adds a pointer to a vertex to the graph's vertexes (pointers).
     *
     * NOTE: Only to be used when inserting vertexes whose ids are sequential
     * (upon the graph's construction), since this function is only invoked in
     * the dataset reading.
     *
     * @param v Pointer to the vertex to be added.
     */
    void addVertex(Vertex* v);

    /**
     * Creates a bidirectional edge between two graph's nodes.
     * Source/destination are interchangeable.
     *
     * @param source Pointer to one of the edge's ends.
     * @param dest Pointer to the other of the edge's ends.
     * @param dist Distance of the edge to be created.
     */
    void addBidirectionalEdge(Vertex* source, Vertex* dest, double dist);

    /**
     * Erases all of the graph's contents.
     * Used when we want to load another graph of the dataset.
     */
    void clear();

    /**
     * @brief Auxiliary for the RandomPath3 function
     *
     * @details This function takes a recursive approach to find a random cycle in the graph and turns it into an iterative function using a stack,
     * to avoid recursion limits.
     *
     * @param path vector of edges to store the path
     *
     * @return true if the path was found, false otherwise
     * */
    bool RandomPathAux3(std::vector<Edge*> &path);

    /**
     * @brief Calculates a random path using the RandomPathAux3 function
     *
     * @details This function returns a random path using the RandomPathAux3 function, that stays restricted to the edges of the graph.
     *
     * @return vector of edges that represent the path found
     * */
    std::vector<Edge*> RandomPath3();

    /**
     * @brief Calculates a random path
     *
     * @details This function returns a random path without the restriction to the edges of the graph,
     * therefore it can create edges that don't exist in the graph.
     *
     * @return vector of edges that represent the path found
     * */
    std::vector<Edge*> RandomPath4();

    /**
     * @brief Auxiliary recursive function for the tspBacktracking function
     *
     * Time Complexity: O(n!) where n is the number of vertices.
     *
     * @param path array with the path
     * @param idx index of the current vertex
     * @param cost cost of the current path
     * */
    void tspBacktrackingAux(unsigned int path[], unsigned int idx, unsigned long cost);

    /**
     * @brief Calculates the minimum cost path using the brute force algorithm with backtracking
     *
     * Time Complexity: O(n!) where n is the number of vertices.
     *
     * @param path array where the path will be stored
     *
     * @return cost of the minimum cost path
     * */
    int tspBacktracking(unsigned int path[]);

    /**
     * @brief Prints the graph.
     * */
    void print() const;

    bool hasCoord = false;

private:
    std::vector<Vertex*> vertexSet;
    unsigned long minCost;
    unsigned int* minPath;
};

/**
 * @brief Verifies if the value is in the array path
 *
 * Time Complexity: O(n) where n is the size of path.
 *
 * @param value value to search
 * @param path array to search
 * @param n size of path
 *
 * @return true if the value is in the array path, else return false
 *
 * */
bool inPath(unsigned int value, unsigned int path[], unsigned int n);

/**
 * @brief Get the Edge that has as source the vertex src and as destination vertex dest
 *
 * Time Complexity: O(u), where u is the degree of the source vertex.
 *
 * @param src source vertex
 * @param dest destination vertex
 *
 * @return Edge that has as source the vertex src and as destination vertex dest
 * */
Edge* get_edge(Vertex* src, Vertex* dest);

/**
 * @brief Get the Edge that has as source the vertex with index src and as destination vertex with index dest and is in the graph g
 *
 * Time Complexity: O(u), where u is the degree of the source vertex.
 *
 * @param g Graph where to search for the edge
 * @param src index of the source vertex
 * @param dest index of the destination vertex
 *
 * @return Edge that has as source the vertex with index src and as destination vertex with index dest and is in the graph g
 * */
Edge* get_edge(const Graph& g, int src, int dest);

/**
 * @brief Calculates the distance between two points, given its coordinates, using the haversine formula
 *
 * @param lat1 latitude of the first point
 * @param lon1 longitude of the first point
 * @param lat2 latitude of the second point
 * @param lon2 longitude of the second point
 *
 * @return distance between the two points
 */
double haversine(double lat1, double lon1, double lat2, double lon2);

/**
 * @brief Auxiliary struct for the RandomPathAux3 function, used to
 *
 * @details Auxiliary struct for the RandomPathAux3 function, used to store the current vertex, the index of the for loop and the index of the path and push it to the stack.
 *
 * @param vertex index of the current vertex
 * @param for_number index of the for loop
 * @param index index of the path
 * */
struct func_call;

#endif //DA_PROJ2_GRAPH_H
