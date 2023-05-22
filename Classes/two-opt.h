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

int pathLengthSq(std::vector<Edge*> &path);
bool do2Opt(std::vector<Edge*> &path, int i, int j);
void printPath(std::string pathName, std::vector<Edge*> &path);
std::vector<Edge*> createRandomPath(Graph g);
std::vector<Edge*> improvePath(std::vector<Edge*> path, Graph g);

#endif
