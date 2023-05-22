#ifndef DA_PROJ2_MENU_H
#define DA_PROJ2_MENU_H

#include <iostream>
#include <chrono>

#include "../Classes/Graph.h"
#include "../Classes/two-opt.h"
#include "../Data Reading/read_data.h"

class Menu {
public:
    Menu();
    void mainMenu();
    Graph getGraph() const;
private:
    Graph graph;
    bool ready = false;
    bool otherHeuristicPrintPath = false;

    void readDataMenu();
    void otherHeuristicMenu();
    void run2Opt(bool withRestriction);
};


#endif //DA_PROJ2_MENU_H
