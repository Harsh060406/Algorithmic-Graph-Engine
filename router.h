#ifndef ROUTER_H
#define ROUTER_H

#include "graph.h"
#include <vector>

using namespace std;

// A custom structure to package our final path data together
struct RouteResult {
    vector<int> path;
    double totalDistance;
    bool success;
};

class Router {
private:
    // The router needs to look at the graph, but shouldn't modify it. 
    // The '&' passes it efficiently, and 'const' protects it.
    const Graph& mapGraph; 

public:
    Router(const Graph& g); // Constructor

    // Our primary routing algorithm
    RouteResult findShortestPathDijkstra(int startId, int endId);
};

#endif