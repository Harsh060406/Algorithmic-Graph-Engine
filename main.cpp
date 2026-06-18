#include <iostream>
#include <chrono> // Standard library for extreme precision time tracking
#include "graph.h"
#include "router.h"

using namespace std;
using namespace std::chrono;

int main() {
    Graph mapGraph;
    cout << "Initializing Algorithmic Graph Execution Engine...\n";

    if (mapGraph.loadNodesFromCSV("nodes.csv") && mapGraph.loadEdgesFromCSV("edges.csv")) {
        cout << "Data parsed successfully!\n";
        mapGraph.printGraphSummary();
        
        // Instantiate the Router
        Router engineRouter(mapGraph);

        // Interactive CLI Loop
        while (true) {
            int startNode, endNode;
            cout << "\n--------------------------------------------------\n";
            cout << "Enter Start Node ID (or -1 to exit): ";
            cin >> startNode;
            
            // Exit condition
            if (startNode == -1) {
                cout << "Exiting engine. Goodbye!\n";
                break;
            }

            cout << "Enter Destination Node ID: ";
            cin >> endNode;

            cout << "\nExecuting Dijkstra's Algorithm...\n";

            // Start High-Resolution Microsecond Timer
            auto start_time = high_resolution_clock::now();

            // Run the algorithm
            RouteResult result = engineRouter.findShortestPathDijkstra(startNode, endNode);

            // Stop Timer and calculate duration
            auto stop_time = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop_time - start_time);

            // Print the profiled results
            if (result.success) {
                cout << "[SUCCESS] Path resolved.\n";
                cout << "Execution Time : " << duration.count() << " microseconds\n";
                cout << "Total Distance : " << result.totalDistance << "\n";
                
                cout << "Route taken    : ";
                for (size_t i = 0; i < result.path.size(); ++i) {
                    cout << result.path[i];
                    if (i < result.path.size() - 1) cout << " -> ";
                }
                cout << "\n";
            } else {
                cout << "[FAILED] No valid path exists between Node " << startNode << " and Node " << endNode << ".\n";
            }
        }

    } else {
        cerr << "CRITICAL ERROR: Failed to load CSV data. Check file paths.\n";
    }

    return 0;
}