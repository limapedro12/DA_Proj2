#ifndef DA_PROJ2_READ_DATA_H
#define DA_PROJ2_READ_DATA_H

#include "../Classes/Graph.h"
#include "../Classes/VertexEdge.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

void readToy(const std::string& name, Graph& g);
void readReal(int graph_no, Graph& g);

#endif //DA_PROJ2_READ_DATA_H
