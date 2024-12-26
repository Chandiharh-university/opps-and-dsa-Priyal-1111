#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <climits>  // Include this header to use INT_MAX
using namespace std;

// Graph representation using an adjacency list
class Graph {
    int V; // Number of nodes (field segments)
    vector<pair<int, int>>* adj; // Adjacency list: (neighbor, cost)

public:
    Graph(int V) {
        this->V = V;
        adj = new vector<pair<int, int>>[V];
    }

    void addEdge(int u, int v, int cost) {
        adj[u].push_back({v, cost});
        adj[v].push_back({u, cost}); // Undirected graph
    }

    // Dijkstra's algorithm to find the shortest path
    vector<int> dijkstra(int src) {
        vector<int> dist(V, INT_MAX);  // Initialize distances to infinity
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }
};

// Function to find critical field segments
void analyzeField(Graph& field, vector<int>& healthData, int droneStart) {
    vector<int> criticalSegments;
    for (int i = 0; i < healthData.size(); i++) {
        if (healthData[i] < 50) { // Threshold for critical health
            criticalSegments.push_back(i);
        }
    }

    if (criticalSegments.empty()) {
        cout << "All segments are healthy! No action needed.\n";
        return;
    }

    // Find shortest paths from the drone's starting position
    vector<int> distances = field.dijkstra(droneStart);

    cout << "Drone Action Plan (Critical Segments):\n";
    for (int segment : criticalSegments) {
        cout << "Segment " << segment << " (Health Index: " << healthData[segment]
             << ") - Distance: " << distances[segment] << "\n";
    }
}

int main() {
    int n = 6; // Number of field segments (nodes)
    Graph field(n);

    // Add edges (representing paths between field segments and their costs)
    field.addEdge(0, 1, 4);
    field.addEdge(0, 2, 2);
    field.addEdge(1, 2, 1);
    field.addEdge(1, 3, 7);
    field.addEdge(2, 4, 3);
    field.addEdge(3, 5, 1);
    field.addEdge(4, 5, 5);

    vector<int> healthData = {45, 85, 30, 90, 50, 40}; // Health indices of segments
    int droneStart = 0; // Drone starts at segment 0

    cout << "Precision Farming with Drones - Using Graph\n";
    cout << "---------------------------------------------\n";

    analyzeField(field, healthData, droneStart);

    return 0;
}
