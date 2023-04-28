#ifndef DA_PROJ2_READ_DATA_H
#define DA_PROJ2_READ_DATA_H

#include "../Classes/Graph.h"
#include "../Classes/VertexEdge.h"

#include <string>
#include <sstream>
#include <fstream>

void readToy(const std::string& filename, Graph& g);
void readReal(const std::string& filename, Graph& g);

#endif //DA_PROJ2_READ_DATA_H
