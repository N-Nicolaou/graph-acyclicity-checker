// Student ID: W2047568 | Name: Nicholas Nicolaou
#include <iostream>
#include "Graph.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputfile>\n";
        return 1;
    }

    string filename = argv[1];
    cout << "Loading graph from: " << filename << "\n";

    Graph g = Graph::fromFile(filename);

    cout << "Graph loaded: " << g.n << " vertices.\n";

    vector<int> eliminationOrder;

    cout << "\n=== Sink Elimination Process ===\n";

    bool acyclic = g.isAcyclic(eliminationOrder);

    cout << "\nElimination order: ";
    for (int v : eliminationOrder) {
        cout << v << " ";
    }
    cout << "\n";

    if (acyclic) {
        cout << "\nResult: Graph is ACYCLIC.\n";
    }
    else {
        cout << "\nResult: Graph is CYCLIC.\n";

        vector<int> cycle;
        if (g.findCycle(cycle)) {
            cout << "\nCycle found: ";
            for (int idx : cycle) {
                cout << g.indexToLabel[idx] << " ";
            }
            cout << "\n";
        }
        else {
            cout << "Error: expected a cycle but none found.\n";
        }
    }

    return 0;
}