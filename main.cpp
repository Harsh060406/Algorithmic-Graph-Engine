#include <iostream>
#include "graph.h"

using namespace std;

int main() {
    Graph mapGraph;

    cout << "Initializing Algorithmic Graph Execution Engine...\n";

    if (mapGraph.loadNodesFromCSV("nodes.csv") && mapGraph.loadEdgesFromCSV("edges.csv")) {
        cout << "Data parsed successfully!\n";
        mapGraph.printGraphSummary();
    } else {
        cerr << "CRITICAL ERROR: Failed to load CSV data. Check file paths.\n";
    }

    return 0;
}