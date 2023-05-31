#ifndef DA_PROJ2_READ_DATA_H
#define DA_PROJ2_READ_DATA_H

#include "../Classes/Graph.h"
#include "../Classes/VertexEdge.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

/**
 * Parses and loads a toy graph from the dataset.
 *
 * @param name Name of the toy graph to be loaded
 * @param g Reference to the Graph class instance the parsed graph information should be load to
 */
void readToy(const std::string& name, Graph& g);

/**
 * Parses and loads a real graph from the dataset.
 *
 * @param name Number of the real graph to be loaded
 * @param g Reference to the Graph class instance the parsed graph information should be load to
 */
void readReal(int graph_no, Graph& g);

/**
 * Parses and loads an extra graph from the dataset.
 *
 * @param node_count Size (number of nodes) of the graph to be loaded, since this attribute is what distinguishes them
 * among the Extra graphs of the given dataset
 * @param g Reference to the Graph class instance the parsed graph information should be load to
 */
void readExtra(unsigned int node_count, Graph& g);

#endif //DA_PROJ2_READ_DATA_H
