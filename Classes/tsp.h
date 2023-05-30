#ifndef TSP_H
#define TSP_H

#include "Graph.h"

#include <vector>

// Finds the minimum spanning tree (MST) traversal order using Prim's algorithm
std::vector<unsigned int> tspMST(const Graph& graph);

// Calculates the TSP tour cost approximation using the MST traversal order
double tspApproximation(const Graph& graph);

#endif