#include "graph.h"
#include <iostream>
#include <string>

int main() {
    Graph g;
    bool running = true;
    std::string filename, graphType;
    int choice, source, destination, flag;

    while (running) {
        std::cout << "\n----- Graph Processing Menu -----\n";
        std::cout << "1. Read Graph from File\n";
        std::cout << "2. Print Adjacency List\n";
        std::cout << "3. Single Source Shortest Path\n";
        std::cout << "4. Single Pair Shortest Path\n";
        std::cout << "5. Print Path\n";
        std::cout << "6. Print Length\n";
        std::cout << "7. Stop\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:  // Read Graph from File
                std::cout << "Enter filename: ";
                std::cin >> filename;
                std::cout << "Enter graph type (D for Directed, UD for Undirected): ";
                std::cin >> graphType;
                std::cout << "Enter flag (1 or 2): ";
                std::cin >> flag;
                g.readGraphFromFile(filename, graphType, flag);
                break;
            case 2:  // Print Adjacency List
                g.printAdjacencyList();
                break;
            case 3:  // Single Source Shortest Path
                std::cout << "Enter source vertex: ";
                std::cin >> source;
                g.singleSourceShortestPath(source); 
                break;
            case 4:  // Single Pair Shortest Path
                std::cout << "Enter source vertex: ";
                std::cin >> source;
                std::cout << "Enter destination vertex: ";
                std::cin >> destination;
                g.singlePairShortestPath(source, destination);
                break;
            case 5:  // Print Path
                std::cout << "Enter source vertex: ";
                std::cin >> source;
                std::cout << "Enter destination vertex: ";
                std::cin >> destination;
                g.printPath(source, destination); 
                break;
            case 6:  // Print Path Length
                std::cout << "Enter source vertex: ";
                std::cin >> source;
                std::cout << "Enter destination vertex: ";
                std::cin >> destination;
                g.printPathLength(source, destination); 
                break;
            case 7:  // Stop
                running = false;
                break;
            default:
                std::cerr << "Invalid choice. Please try again.\n";
        }
    }

    std::cout << "Program terminated.\n";
    return 0;
}

