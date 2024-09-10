#ifndef MAIN_H
#define MAIN_H

#include "graph.h"

class NavigationSystem {
private:
    Graph* graph;

public:
    NavigationSystem();
    ~NavigationSystem();
    void run();
};

#endif // MAIN_H



