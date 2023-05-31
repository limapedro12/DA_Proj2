#ifndef DA_PROJ2_MENU_H
#define DA_PROJ2_MENU_H

#include <iostream>
#include <chrono>

#include "../Classes/Graph.h"
#include "../Classes/two-opt.h"
#include "../Data Reading/read_data.h"

/**
 * @brief A UI Menu class.
 *
 * This is a class that provides the program's UI menu and submenus.
 */
class Menu {
public:
    /**
     * Constructs a menu and creates a Graph to model the data that will be read.
     */
    Menu();
    /**
     * Provides the UI main menu. Calls private functions that provide the submenus.
     */
    void mainMenu();
private:
    /**
     * Graph that models the desired graph of the dataset.
     */
    Graph graph;

    /**
     * Whether a graph has been loaded from the dataset.
     */
    bool ready = false;

    /**
     * Whether the calculated path using the other heuristic (T2.3) should be printed.
     */
    bool otherHeuristicPrintPath = false;

    /**
     * Provides the submenu that allows to load a dataset.
     */
    void readDataMenu();

    /**
     * Provides the submenu that allows to use the other heuristic (T2.3).
     */
    void otherHeuristicMenu();
    void run2Opt(bool withRestriction);
};


#endif //DA_PROJ2_MENU_H
