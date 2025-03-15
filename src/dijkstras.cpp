#include "dijkstras.h"
#include <algorithm>
using namespace std;

struct Node {
    int vertex, weight;
    Node(int v, int w) : vertex(v), weight(w) {}

    bool operator>(const Node& other) const {
        return weight > other.weight;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(Node(source, 0));
    distance[source] = 0;
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;
        if (visited[u]) continue;
        visited[u] = true;
        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) return path;
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    if (v.empty()) {
        cout << "No path found." << endl;
        return;
    }
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}