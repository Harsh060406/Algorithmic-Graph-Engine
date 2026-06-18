#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    int numNodes = 10000;
    int edgesPerNode = 4; // This will generate roughly 40,000 connecting roads

    cout << "Generating massive map network...\n";

    // 1. Generate 10,000 random coordinates
    ofstream nodeFile("nodes.csv");
    nodeFile << "node_id,latitude,longitude\n";
    for (int i = 1; i <= numNodes; ++i) {
        double lat = 29.0 + (rand() % 1000) / 1000.0;
        double lon = 77.0 + (rand() % 1000) / 1000.0;
        nodeFile << i << "," << lat << "," << lon << "\n";
    }
    nodeFile.close();

    // 2. Generate 40,000 random roads connecting them
    ofstream edgeFile("edges.csv");
    edgeFile << "source_node,target_node,weight\n";
    srand(time(0));
    
    for (int i = 1; i <= numNodes; ++i) {
        for (int e = 0; e < edgesPerNode; ++e) {
            int target = (rand() % numNodes) + 1;
            if (target != i) {
                double weight = (rand() % 100) / 10.0 + 0.1; // Random distance between 0.1 and 10.0
                edgeFile << i << "," << target << "," << weight << "\n";
            }
        }
    }
    edgeFile.close();

    cout << "SUCCESS: Overwrote CSVs with 10,000 nodes and ~40,000 edges.\n";
    return 0;
}