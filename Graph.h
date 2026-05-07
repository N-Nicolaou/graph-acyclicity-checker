// Student ID: W2047568 | Name: Nicholas Nicolaou
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <map>

class Graph {
private:
    // This is out-degree of each vertex and -1 means vertex has been removed
    std::vector<int> outdeg;

    // We also have DFS helper for cycle detection
    bool dfsCycle(int v,
        std::vector<bool>& visited,
        std::vector<bool>& inStack,
        std::vector<int>& parent,
        std::vector<int>& cycle);

public:
    int n;  // Number of vertices

    // This is adjacency list
    std::vector<std::vector<int>> adj;

    // This is reverse adjacency list for sink removal and efficiency
    std::vector<std::vector<int>> radj;

    // This label internal index
    std::map<int, int> labelToIndex;
    std::vector<int>   indexToLabel;

    Graph(int n);

    void addEdge(int u, int v);

    bool hasSink(int& sinkVertex) const;

    void removeVertex(int v);

    // The Sink elimination acyclicity check
    bool isAcyclic(std::vector<int>& eliminationOrder);

    // Finds and return a cycle and returns false if none
    bool findCycle(std::vector<int>& cycle);

    // Parse graph from a file - handles both plain edge-pair files and
    // files with an optional vertex count on the first line
    static Graph fromFile(const std::string& filename);
};

#endif