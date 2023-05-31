#ifndef THREE_OPT_H
#define THREE_OPT_H

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
#include "two-opt.h"

using namespace std;

/**
 * @brief This function reverses the order of the edges between i and j
 *
 * Time Complexity: O(n) where n is the number of edges in the path
 *
 * @param path vector of edges that represent the path
 * @param i index of the first edge
 * @param j index of the second edge
 */
void reverse(vector<Edge*> &path, int i, int j);

/**
 * @brief This function copies the edges between startPath and endPath of path to newPath
 *
 * Time Complexity: O(n) where n is the number of edges in the path
 *
 * @param path vector of edges that represent the path from where the edges are going to be copied
 * @param newPath vector of edges that represent the new path where the edges are going to be copied
 * @param startPath index of the first edge of the copy
 * @param endPath index of the last edge of the copy
 * @param startNewPath index of the first edge of the paste
 */
void copy(vector<Edge*> &path, vector<Edge*> &newPath, int startPath, int endPath, int startNewPath);

/**
 * @brief Calculates which of the 7 possible 3-opt swaps is the best
 *
 * @details This function sums the distance of the 3 edges that are going to be removed
 * and then compares the sum with the sum of the 3 edges that could be added
 * after that returns the number that represents the option that has the lowest sum
 * If the best option is to not do the swap returns 0
 *
 * Time Complexity: O(1)
 *
 * @param path vector of edges that represent the path
 * @param i index of the first edge
 * @param j index of the second edge
 * @param k index of the third edge
 * @param adj adjacency matrix of the graph
 *
 * @return Returns a number between 0 and 7 that represents the best option
 * */
int verify3Opt(vector<Edge*> &path, int i, int j, int k, vector<vector<Edge*>> adj);

/**
 * @brief This functions does a 3-opt swap of three edges of a path
 *
 * @details This function does a 3-opt swap of to edges of a path,
 * therefore it removes the edges i, j, k, creating 3 sub-tours and
 * then reconnects them in one of 7 possible ways, defined in the
 * argument selectedPath.
 *
 * Time Complexity: O(n) where n is the number of edges in the path
 *
 * @param path vector of edges that represent the path
 * @param i index of the first edge
 * @param j index of the second edge
 *
 * @return true if the swap was done, false otherwise
 * */
bool do3Opt(vector<Edge*> &path, int i, int j, int k, int selectedPath, vector<vector<Edge*>> adj);

/**
 * @brief This function calculates the number of combinations of n elements taken k at a time
 *
 * @param n total number of elements
 * @param k number of elements taken at a time
 *
 * @return number of combinations of n elements taken k at a time
 */
unsigned long combinations(unsigned n, unsigned k);

/**
 * @brief This function prints the progress of the algorithm
 *
 * @details This function prints the the percentage of the algorithm that has already been executed
 * This function only prints the percentages that are multiples of 10 (10%, 20%, 30%, ...)
 *
 * @param proportion proportion of the algorithm that has already been executed
 */
void printProgress(double proportion);

/**
 * @brief This functions improves a path using the 3-opt algorithm, restricted to the edges of the graph
 *
 * @details This function improves a path using the 3-opt algorithm.
 * This Algorithm starts with a given path and tries to improve it by doing a single execution of 3-opt.
 * For every comibantion of three diferent edges the algortithm verifies if one of thev 7 possible swap improves the path,
 * it is done, othewise if continues to the next combination of 3 edges.
 * It first calls the function verify3Opt to check if the swap improves the path and which is the best option,
 * and then it calls the function do3Opt to do the swap.
 * Before running the 3-opt algorithm, it runs the 2-opt algorithm to get better results.
 *
 * This function returns a path restricted by the edges of the graph
 *
 * The return of this function is not guaranteed to be the best path possible, it is just an heuristic
 *
 * Time Complexity: O(n^4) where n is the number of edges in the graph
 *
 * @param path vector of edges that represent the path
 * @param g graph that contains the edges of the path and that restrictes the edges that can be added
 *
 * @return an improved path restricted by the edges of the graph
 */
std::vector<Edge*> improvePath3Opt(std::vector<Edge*> path, Graph g);

/**
 * @brief This functions improves a path using the 3-opt algorithm, without restrictions
 *
 * @details This function improves a path using the 3-opt algorithm.
 * This Algorithm starts with a given path and tries to improve it by doing a single execution of 3-opt.
 * For every comibantion of three diferent edges the algortithm verifies if one of thev 7 possible swap improves the path,
 * it is done, othewise if continues to the next combination of 3 edges.
 * It first calls the function verify3Opt to check if the swap improves the path and which is the best option,
 * and then it calls the function do3Opt to do the swap.
 * Before running the 3-opt algorithm, it runs the 2-opt algorithm to get better results.
 *
 * This function returns an improved path without restrictions.
 *
 * The return of this function is not guaranteed to be the best path possible, it is just an heuristic.
 *
 * Time Complexity: O(n^4) where n is the number of edges in the graph
 *
 * @param path vector of edges that represent the path
 * @param g graph that contains the edges of the path and that restrictes the edges that can be added
 *
 * @return an improved path without restrictions
 */
std::vector<Edge*> improvePathAll3Opt(std::vector<Edge*> path, Graph g);


#endif
