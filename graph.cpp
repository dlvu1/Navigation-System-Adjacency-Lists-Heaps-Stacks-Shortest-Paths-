#include "graph.h"
#include "heap.h"
#include "stack.h"
#include "structures.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cfloat>
#include <algorithm>

Graph::Graph() : V(nullptr), ADJ(nullptr), numOfVertices(0), isDirected(false) {}

Graph::~Graph() {
    clearGraph();
}

void Graph::readGraphFromFile(const std::string& filename, const std::string& graphType, int flag) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    isDirected = (graphType == "D");
    int numOfEdges;
    file >> numOfVertices >> numOfEdges;

    V = new VERTEX[numOfVertices];
    ADJ = new NODE*[numOfVertices];

    // Initialize vertices and adj lists
    for (int i = 0; i < numOfVertices; ++i) {
        V[i].index = i;  // Set the vertex index
        V[i].key = FLT_MAX;
        V[i].pi = nullptr;
        ADJ[i] = nullptr;
    }

    int edgeIndex, u, v;
    float w;
    for (int i = 0; i < numOfEdges; ++i) {
        file >> edgeIndex >> u >> v >> w;
        u--; v--;

        // Add edge from u to v
        addEdge(u, v, w, edgeIndex, flag);

        // For undirected graphs, add edge from v to u
        if (!isDirected) {
            addEdge(v, u, w, edgeIndex, flag);
        }
    }
}

void Graph::addEdge(int u, int v, float w, int edgeIndex, int flag) {
    NODE* newNode = new NODE{edgeIndex, u, v, w, nullptr};
    addNode(u, newNode, flag);
}

void Graph::addNode(int vertex, NODE* node, int flag) {
    if (flag == 1) {
        insertNodeAtFront(vertex, node);
    } else {
        insertNodeAtRear(vertex, node);
    }
}

void Graph::printAdjacencyList() const {
    for (int i = 0; i < numOfVertices; ++i) {
        std::cout << "ADJ[" << (i + 1) << "]:";
        for (NODE* node = ADJ[i]; node != nullptr; node = node->next) {
            std::cout << "-->[" << node->u + 1 << " " << node->v + 1 << ": " << std::fixed << std::setprecision(2) << node->w << "]";
        }
        std::cout << std::endl;
    }
}

void Graph::singleSourceShortestPath(int startVertex) {
    startVertex--;

    if (startVertex < 0 || startVertex >= numOfVertices) {
        std::cerr << "Invalid start vertex index." << std::endl;
        return;
    }

    // Initialize vertices
    for (int i = 0; i < numOfVertices; i++) {
        V[i].key = FLT_MAX;
        V[i].pi = nullptr;
    }

    // Set the start vertex's key to 0
    V[startVertex].key = 0;

    // Create an array of pointers to vertices
    VERTEX** vertices = new VERTEX*[numOfVertices];
    for (int i = 0; i < numOfVertices; i++) {
        vertices[i] = &V[i];
    }

    MinHeap heap(numOfVertices);
    heap.buildHeap(vertices, numOfVertices);

    while (!heap.isEmpty()) {
        VERTEX* u = heap.extractMin();
        for (NODE* v = ADJ[u->index]; v != nullptr; v = v->next) {
            if (V[v->v].key > u->key + v->w) {
                V[v->v].key = u->key + v->w;
                V[v->v].pi = u;
                heap.decreaseKey(&V[v->v], V[v->v].key);
            }
        }
    }

    delete[] vertices; // Properly deallocate memory
}


void Graph::singlePairShortestPath(int startVertex, int endVertex) {
    startVertex--;
    endVertex--;

    for (int i = 0; i < numOfVertices; i++) {
        V[i].key = FLT_MAX;
        V[i].pi = nullptr;
    }

    V[startVertex].key = 0;
    
    // Declare vertices array outside the loop
    VERTEX** vertices = new VERTEX*[numOfVertices];
    for (int i = 0; i < numOfVertices; i++) {
        vertices[i] = &V[i];
    }

    MinHeap heap(numOfVertices);
    heap.buildHeap(vertices, numOfVertices);

    while (!heap.isEmpty()) {
        VERTEX* u = heap.extractMin();

        if (u->index == endVertex) { // Stop if end vertex is reached
            return;
        }

        for (NODE* v = ADJ[u->index]; v != nullptr; v = v->next) {
            if (V[v->v].key > u->key + v->w) {
                V[v->v].key = u->key + v->w;
                V[v->v].pi = u;
                heap.decreaseKey(&V[v->v], V[v->v].key);
            }
        }
    } delete[] vertices; // Clean up
}


void Graph::printPath(int startVertex, int endVertex) const {
    startVertex--; 
    endVertex--;

    if (V[endVertex].key == FLT_MAX) {
        std::cout << "There is no path from " << startVertex + 1 << " to " << endVertex + 1 << ".\n";
        return;
    }

    Stack pathStack(numOfVertices);

    // Backtrack from the destination to the source
    for (VERTEX* v = &V[endVertex]; v != nullptr; v = v->pi) {
        pathStack.push(v);
        if (v->index == startVertex) break;
    }

    std::cout << "The shortest path from " << startVertex + 1 << " to " << endVertex + 1 << " is:\n";

    // Pop from the stack and print the path with costs
    double totalCost = 0.0;
    while (!pathStack.isEmpty()) {
        VERTEX* vertex = pathStack.pop();

        std::cout << "[" << vertex->index + 1 << ":     " << std::fixed << std::setprecision(2) << totalCost << "]";
        if (!pathStack.isEmpty()) {
            totalCost += calculateEdgeCost(vertex, pathStack.peek());
            std::cout << "-->";
        }
    }
    std::cout << std::endl;
}

float Graph::calculateEdgeCost(VERTEX* fromVertex, VERTEX* toVertex) const {
    for (NODE* v = ADJ[fromVertex->index]; v != nullptr; v = v->next) {
        if (v->v == toVertex->index) {
            return v->w;
        }
    }
    return 0.0;
}

// Implementation to print the length of the path between two vertices
void Graph::printPathLength(int startVertex, int endVertex) const {
    startVertex--; // Adjust for 0-based indexing
    endVertex--;

    // Check if a path exists
    if (V[endVertex].key == FLT_MAX) {
        std::cout << "There is no path from " << startVertex + 1 << " to " << endVertex + 1 << ".\n";
        return;
    }

    std::cout << "The length of the shortest path from " << startVertex + 1
              << " to " << endVertex + 1 << " is: "
              << std::fixed << std::setprecision(2) << V[endVertex].key << std::endl;
}

void Graph::insertNodeAtFront(int u, NODE* node) {
    node->next = ADJ[u];
    ADJ[u] = node;
}

void Graph::insertNodeAtRear(int u, NODE* node) {
    if (ADJ[u] == nullptr) {
        ADJ[u] = node;
    } else {
        NODE* current = ADJ[u];
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = node;
    }
}

void Graph::clearGraph() {
    for (int i = 0; i < numOfVertices; ++i) {
        NODE* current = ADJ[i];
        while (current != nullptr) {
            NODE* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] ADJ;
    delete[] V;
}
