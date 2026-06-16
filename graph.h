#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

// Represents a coordinate point on a map
struct MapNode {
    int id;
    double latitude;
    double longitude;
};

// Represents a directed, weighted road segment between two points
struct MapEdge {
    int target;
    double weight;
};

class Graph {
private:
    // Maps a Node ID to its coordinate details
    std::unordered_map<int, MapNode> nodeRegistry;

    // Adjacency List: Maps a Node ID to a list of all outward Edges connecting to it
    std::unordered_map<int, std::vector<MapEdge>> adjacencyList;

public:
    void addNode(int id, double lat, double lon);
    void addEdge(int source, int target, double weight);

    // Methods to parse our datasets
    bool loadNodesFromCSV(const std::string& filename);
    bool loadEdgesFromCSV(const std::string& filename);

    void printGraphSummary() const;
    
    const std::unordered_map<int, MapNode>& getNodes() const { return nodeRegistry; }
    const std::vector<MapEdge>& getNeighbors(int nodeId) const;
};

#endif