// Student ID: W2047568 | Name: Nicholas Nicolaou
#include "Graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

Graph::Graph(int n) : n(n) {
    adj.resize(n);
    radj.resize(n);
    outdeg.assign(n, 0);
    indexToLabel.resize(n, 0);
    // This is Identity mapping (0-based labels)
    for (int i = 0; i < n; i++) indexToLabel[i] = i;
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    radj[v].push_back(u);
    outdeg[u]++;
}

bool Graph::hasSink(int& sinkVertex) const {
    for (int i = 0; i < n; i++) {
        if (outdeg[i] == 0) {
            sinkVertex = i;
            return true;
        }
    }
    return false;
}

void Graph::removeVertex(int v) {
    for (int from : radj[v]) {
        if (outdeg[from] > 0) {
            outdeg[from]--;
        }
    }
    radj[v].clear();
    adj[v].clear();
    outdeg[v] = -1;
}

bool Graph::isAcyclic(vector<int>& eliminationOrder) {
    eliminationOrder.clear();
    int removedCount = 0;

    while (removedCount < n) {
        int sink = -1;
        if (!hasSink(sink)) {
            return false;
        }
        eliminationOrder.push_back(indexToLabel[sink]);
        removeVertex(sink);
        removedCount++;
    }
    return true;
}

bool Graph::dfsCycle(int v,
    vector<bool>& visited,
    vector<bool>& inStack,
    vector<int>& parent,
    vector<int>& cycle) {
    visited[v] = true;
    inStack[v] = true;

    for (int to : adj[v]) {
        if (outdeg[to] == -1) continue;  // I can skip removed vertices

        if (!visited[to]) {
            parent[to] = v;
            if (dfsCycle(to, visited, inStack, parent, cycle))
                return true;
        }
        else if (inStack[to]) {
            cycle.clear();
            cycle.push_back(to);
            int cur = v;
            while (cur != to) {
                cycle.push_back(cur);
                cur = parent[cur];
            }
            cycle.push_back(to);
            reverse(cycle.begin(), cycle.end());
            return true;
        }
    }

    inStack[v] = false;
    return false;
}

bool Graph::findCycle(vector<int>& cycle) {
    vector<bool> visited(n, false);
    vector<bool> inStack(n, false);
    vector<int>  parent(n, -1);

    for (int i = 0; i < n; i++) {
        if (outdeg[i] != -1 && !visited[i]) {
            if (dfsCycle(i, visited, inStack, parent, cycle))
                return true;
        }
    }
    return false;
}

Graph Graph::fromFile(const string& filename) {
    ifstream in(filename);
    if (!in) {
        cerr << "Error: cannot open file " << filename << "\n";
        exit(1);
    }

    vector<pair<int, int>> edges;
    int maxLabel = -1;

    string line;
    while (getline(in, line)) {
        
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (line.empty()) continue;

        istringstream iss(line);
        int a, b;
        if (!(iss >> a)) continue;

        if (!(iss >> b)) {
            // Only one number on the line
            continue;
        }

        // Two numbers
        edges.push_back({ a, b });
        maxLabel = max(maxLabel, max(a, b));
    }

    int n = maxLabel + 1;
    Graph g(n);

    for (int i = 0; i < n; i++) {
        g.labelToIndex[i] = i;
        g.indexToLabel[i] = i;
    }

    for (auto& [u, v] : edges) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cerr << "Warning: edge " << u << "->" << v << " out of range, skipping\n";
            continue;
        }
        g.addEdge(u, v);
    }

    return g;
}