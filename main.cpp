#include <iostream>

#include "Data Reading/read_data.h"
#include "Classes/Graph.h"

#include <algorithm>

int main() {
    Graph g;

    readToy("../Project2Data/Toy-Graphs/shipping.csv", g);

    std::vector<Vertex*> v = g.getVertexSet();

    std::sort(v.begin(), v.end(), [](Vertex* a, Vertex* b) {return a->getId() < b->getId();});

    for (Vertex* v : v) v->print();
}
