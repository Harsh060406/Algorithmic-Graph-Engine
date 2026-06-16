#include "graph.h"
#include <fstream>
#include <sstream>

using namespace std;

void Graph::addNode(int id, double lat, double lon) {
    nodeRegistry[id] = {id, lat, lon};
}

void Graph::addEdge(int source, int target, double weight) {
    adjacencyList[source].push_back({target, weight});
}

bool Graph::loadNodesFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, latStr, lonStr;
        
        getline(ss, idStr, ',');
        getline(ss, latStr, ',');
        getline(ss, lonStr, ',');

        addNode(stoi(idStr), stod(latStr), stod(lonStr));
    }
    return true;
}

bool Graph::loadEdgesFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string srcStr, tgtStr, weightStr;
        
        getline(ss, srcStr, ',');
        getline(ss, tgtStr, ',');
        getline(ss, weightStr, ',');

        addEdge(stoi(srcStr), stoi(tgtStr), stod(weightStr));
    }
    return true;
}

void Graph::printGraphSummary() const {
    cout << "Graph Engine loaded with " << nodeRegistry.size() << " nodes and " 
         << adjacencyList.size() << " source nodes with outgoing edges.\n";
}

const vector<MapEdge>& Graph::getNeighbors(int nodeId) const {
    static const vector<MapEdge> empty;
    auto it = adjacencyList.find(nodeId);
    if (it != adjacencyList.end()) {
        return it->second;
    }
    return empty;
}