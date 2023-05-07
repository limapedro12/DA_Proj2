#ifndef DA_PROJ2_MENU_H
#define DA_PROJ2_MENU_H

#include <iostream>
#include <chrono>

#include "../Classes/Graph.h"
#include "../Data Reading/read_data.h"

class Menu {
public:
    Menu();
    void mainMenu();
    Graph getGraph() const;
private:
    Graph graph;
    bool ready = false;

    void readDataMenu();
};


#endif //DA_PROJ2_MENU_H
