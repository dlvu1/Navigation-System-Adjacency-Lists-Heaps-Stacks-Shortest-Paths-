#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <cfloat>

// Structure for vertices in the graph
typedef struct VERTEX {
    VERTEX* pi;    // pi value in Dijkstra’s algorithm
    float key;   // key value in Dijkstra’s algorithm
    int index;    // vertex number
    // Add any other data members if needed

    VERTEX() : key(FLT_MAX), pi(nullptr), index(0) {}  // Constructor
} VERTEX;

// Structure for nodes on the adjacency lists
typedef struct NODE {
    int index;   // node number
    int u;       // starting vertex
    int v;       // ending vertex
    float w;     // edge weight
    NODE* next;  // pointer to the next node in the list

    // Default constructor
    NODE() : index(0), u(0), v(0), w(0.0), next(nullptr) {}  

    // Constructor with parameters
    NODE(int idx, int startVertex, int endVertex, float weight, NODE* nxt)
        : index(idx), u(startVertex), v(endVertex), w(weight), next(nxt) {}
} NODE;

#endif // STRUCTURES_H

