#include <iostream>
#include "graph.h"
#include "router.h"

using namespace std;

int main() {
    Graph mapGraph;
    cout << "Initializing Algorithmic Graph Execution Engine...\n";

    if (mapGraph.loadNodesFromCSV("nodes.csv") && mapGraph.loadEdgesFromCSV("edges.csv")) {
        cout << "Data parsed successfully!\n";
        
        // Instantiate the Router with our loaded Graph
        Router engineRouter(mapGraph);

        cout << "\nCalculating shortest path from Node 1 to Node 3...\n";
        RouteResult result = engineRouter.findShortestPathDijkstra(1, 3);

        if (result.success) {
            cout << "Path found! Total Distance: " << result.totalDistance << "\n";
            cout << "Route: ";
            for (size_t i = 0; i < result.path.size(); ++i) {
                cout << result.path[i];
                if (i < result.path.size() - 1) cout << " -> ";
            }
            cout << "\n";
        } else {
            cout << "No valid path exists between these nodes.\n";
        }

    } else {
        cerr << "CRITICAL ERROR: Failed to load CSV data. Check file paths.\n";
    }

    return 0;
}