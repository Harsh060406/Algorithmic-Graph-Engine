#include "router.h"
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

// Constructor linking the graph to the router
Router::Router(const Graph& g) : mapGraph(g) {}

RouteResult Router::findShortestPathDijkstra(int startId, int endId) {
    RouteResult result;
    result.success = false;
    result.totalDistance = 0.0;

    // Track the shortest known distance to each node. Initialize to "Infinity".
    unordered_map<int, double> distances;
    // Track where we came from to reconstruct the final path backwards.
    unordered_map<int, int> previous;

    for (const auto& pair : mapGraph.getNodes()) {
        distances[pair.first] = numeric_limits<double>::infinity();
    }
    
    // The distance from the start node to itself is always 0
    distances[startId] = 0.0;

    // A Min-Heap Priority Queue: Stores pairs of {distance, node_id}
    // It automatically keeps the node with the lowest distance at the top.
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({0.0, startId});

    while (!pq.empty()) {
        double currentDist = pq.top().first;
        int currentId = pq.top().second;
        pq.pop();

        // If we reached our destination, stop calculating
        if (currentId == endId) {
            result.success = true;
            break;
        }

        // If we already found a faster way to this node earlier, ignore this outdated path
        if (currentDist > distances[currentId]) continue;

        // Check all outgoing roads (edges) from our current node
        for (const auto& edge : mapGraph.getNeighbors(currentId)) {
            double newDist = currentDist + edge.weight;

            // If we found a strictly shorter path to the neighbor, update it
            if (newDist < distances[edge.target]) {
                distances[edge.target] = newDist;
                previous[edge.target] = currentId;
                pq.push({newDist, edge.target});
            }
        }
    }

    if (!result.success) return result;

    // Reconstruct the path by walking backwards from the destination
    int current = endId;
    while (current != startId) {
        result.path.push_back(current);
        current = previous[current];
    }
    result.path.push_back(startId);

    // Flip the path so it goes from Start -> End
    reverse(result.path.begin(), result.path.end());
    result.totalDistance = distances[endId];

    return result;
}