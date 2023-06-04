#ifndef TSP_H
#define TSP_H

#include "Graph.h"

#include <vector>

// Finds the minimum spanning tree (MST) traversal order using Prim's algorithm
// Calculates the TSP tour cost approximation using the MST traversal order
/**
 * @brief Calculates a path using the Minimum Spanning Tree (MST) that will be used for the Traveling Salesman Problem (TSP).
 *
 * @details This function constructs a minimum spanning tree of the given graph and generates an order of vertices to visit based on the MST.
 *
 * Time Complexity: O((V + E) log (V)).
 *
 * @param graph
 *
 * @return A vector of unsigned integers representing the order in which vertices should be visited in the approximate TSP solution.
 *         The vector is empty if the graph has no vertices.
 */
std::vector<unsigned int> tspMST(const Graph& graph);

// Calculates the TSP tour cost approximation using the MST traversal order
/**
 * @brief Calculates an approximate solution to the Traveling Salesman Problem (TSP) using the MST heuristic and calculates the total cost of the path given by it.
 *
 * @details This function constructs a minimum spanning tree (MST) of the given graph using the `tspMST` function. It then calculates the total cost of the path returned by tspMST.
 *
 * Time Complexity: O((V + E) log (V)).
 *
 * @param graph
 *
 * @return The total cost of the approximate TSP solution path.
 */
double tspApproximation(const Graph& graph);


#endif