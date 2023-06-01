#ifndef D2_OPT_H
#define D2_OPT_H

#include <vector>
#include <list>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_set>
#include <queue>
#include <stack>
#include <ctgmath>
#include "Graph.h"

/**
 * @brief Calculates the sum of the squared distances of a path
 *
 * @details This function calculates the sum of the squared distances of a path
 *
 * Time Complexity: O(n) where n is the number of edges in the path
 *
 * @param path vector of edges that represent the path
 *
 * @return sum of the squared distances of the path
 * */
int pathLengthSq(std::vector<Edge*> &path);

/**
 * @brief This functions does a 2-opt swap of to edges of a path
 *
 * @details This function does a 2-opt swap of to edges of a path,
 * therefore it adds an edge from source of i to dest of j and from source of j to dest of i
 * and reverses the order of the edges between i and j
 *
 * This is only used in the function that is restricted to the edges of the graph
 *
 * Time Complexity: O(n) where n is the number of edges in the path
 *
 * @param path vector of edges that represent the path
 * @param i index of the first edge
 * @param j index of the second edge
 *
 * @return true if the swap was done, false otherwise
 * */
bool do2Opt(std::vector<Edge*> &path, int i, int j);

/**
 * @brief This functions prints a give path
 *
 *
 * @param pathName name of the path
 * @param path vector of edges that represent the path
 * */
void printPath(std::string pathName, std::vector<Edge*> &path);

/**
 * @brief This functions improves a path using the 2-opt algorithm restricted to the edges of the graph
 *
 * @details This function improves a path using the 2-opt algorithm.
 * This Algorithm starts with a given path and tries to improve it by doing 2-opt swaps.
 * For every combination of two edges it verifyies if the swap improves the path,
 * if it is does, the swap is done, otherwise it continues to the next combination of edges.
 * This verification can be done in O(1) time the following formula:
 * lenghtDelata = (dist(i, j)^2 + dist(i+1, j+1)^2) - (dist(i, i+1)^2 + dist(j, j+1)^2)
 * if lenghtDelta > 0 then the swap improves the path
 *
 * This function returns a path restricted by the edges of the graph
 *
 * The return of this function is not guaranteed to be the best path possible,
 * it is just an heuristic
 *
 * Time Complexity: O(n^3*log(n)) where n is the number of edges in the graph
 *
 * @param path vector of edges that represent the path
 * @param g graph that contains the edges of the path and that restrictes the edges that can be added
 * @return an 2-opt heuritic to the TSP problem, restricted by the edges of the graph
 */
std::vector<Edge*> improvePath(std::vector<Edge*> path, Graph g, bool print = true);

/**
 * @brief This functions does a 2-opt swap of to edges of a path
 *
 * @details This function does a 2-opt swap in the given path,
 * therefore reverses the order of the edges between i and j
 *
 * This is only used in the function that isn't restricted to the edges of the graph
 *
 * Time Complexity: O(n) where n is the number of edges in the path
 *
 * @param path vector of edges that represent the path
 * @param i index of the first edge
 * @param j index of the second edge
 *
 * @return true if the swap was done, false otherwise
 * */
bool do2OptAll(std::vector<int> &path, int i, int j);

/**
 * @brief This function transforms a path of the indexes of vertexes into a path of edges
 *
 * Time Complexity: O(n) where n is the number of edges in the path
 *
 * @param path path of the indexes of vertexes
 * @param path2 vector to store the path of edges
 * @param g the graph that contains the edges
 */
void vIntToVEdge(std::vector<int> &path, std::vector<Edge*> &path2, Graph g);

/**
 * @brief This functions improves a path using the 2-opt algorithm without restrictions
 *
 * @details This function improves a path using the 2-opt algorithm.
 * This Algorithm starts with a given path and tries to improve it by doing 2-opt swaps.
 * For every combination of two edges it verifyies if the swap improves the path,
 * if it is does, the swap is done, otherwise it continues to the next combination of edges.
 * This verification can be done in O(1) time the following formula:
 * lenghtDelata = (dist(i, j)^2 + dist(i+1, j+1)^2) - (dist(i, i+1)^2 + dist(j, j+1)^2)
 * if lenghtDelta > 0 then the swap improves the path
 *
 * This function returns a path that is not restricted by the edges of the graph
 *
 * Time Complexity: O(n^3*log(n)) where n is the number of edges in the graph
 *
 * The return of this function is not guaranteed to be the best path possible,
 * it is just an heuristic
 *
 * @param path vector of edges that represent the path
 * @param g graph that contains the edges of the path and that restrictes the edges that can be added
 * @return an 2-opt heuritic to the TSP problem without restrictions
 */
std::vector<Edge*> improvePathAll(std::vector<Edge*> path, Graph g, bool print = true);

/**
 * @brief This function calculates the distance squared between two vertexes
 * @param v1 first vertex
 * @param v2 second vertex
 * @return the distance squared between the two vertexes
 */
double dist2(const Vertex* v1, const Vertex* v2);

#endif
