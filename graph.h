#ifndef GRAPH_H
#define GRAPH_H

#include "structures.h"
#include <string>

class Graph {
private:
    VERTEX* V;          // Array of vertex objects
    NODE** ADJ;         // Array of adjacency lists
    int numOfVertices;  // Number of vertices in the graph
    bool isDirected;    // Flag for directed/undirected graph
    
    void addNode(int vertex, NODE* node, int flag);
    void addEdge(int u, int v, float w, int edgeIndex, int flag);

public:
    Graph(); 
    ~Graph();

    void readGraphFromFile(const std::string& filename, const std::string& graphType, int flag);
    void printAdjacencyList() const;
    void singleSourceShortestPath(int startVertex);
    void singlePairShortestPath(int startVertex, int endVertex);
    void printPath(int startVertex, int endVertex) const;
    void printPathLength(int startVertex, int endVertex) const;
    float calculateEdgeCost(VERTEX* fromVertex, VERTEX* toVertex) const;

private:
    void insertNodeAtFront(int u, NODE* node);
    void insertNodeAtRear(int u, NODE* node);
    void clearGraph();
    // Add any other helper functions if needed
};

#endif // GRAPH_H
