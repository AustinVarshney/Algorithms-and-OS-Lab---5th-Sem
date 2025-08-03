#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Edge {
    int to;
    bool isBackbone;
};

vector<int> findPreferredPath(int n, int source, int dest, vector<vector<Edge>>& graph) {
    vector<int> dist(n, INT8_MAX);
    vector<int> parent(n, -1);
    deque<int> dq;

    dist[source] = 0;
    dq.push_front(source);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.isBackbone ? 0 : 1;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;

                if (weight == 0)
                    dq.push_front(v);
                else
                    dq.push_back(v);
            }
        }
    }

    // Reconstruct path
    vector<int> path;
    if (dist[dest] == INT8_MAX) return path; // no path

    for (int at = dest; at != -1; at = parent[at])
        path.push_back(at);

    reverse(path.begin(), path.end());
    return path;
}

int main() {
    // int n = 6; // Number of nodes
    int n = 5; // Number of nodes
    vector<vector<Edge>> graph(n);

    // // Add edges: graph[from].push_back({to, isBackbone});
    // graph[0].push_back({1, true});
    // graph[1].push_back({0, true});

    // graph[1].push_back({2, false});
    // graph[2].push_back({1, false});

    // graph[0].push_back({3, false});
    // graph[3].push_back({0, false});

    // graph[3].push_back({4, true});
    // graph[4].push_back({3, true});

    // graph[4].push_back({5, true});
    // graph[5].push_back({4, true});

    // graph[2].push_back({5, false});
    // graph[5].push_back({2, false});

    // int source = 0, destination = 5;

    graph[0].push_back({1, true});
    graph[1].push_back({0, true});

    graph[2].push_back({1, true});
    graph[1].push_back({2, true});

    graph[2].push_back({3, true});
    graph[3].push_back({2, true});

    graph[4].push_back({3, true});
    graph[3].push_back({4, true});

    graph[4].push_back({0, false});
    graph[0].push_back({4, false});

    int source = 0, destination = 4;

    vector<int> path = findPreferredPath(n, source, destination, graph);

    if (!path.empty()) {
        cout << "Preferred path (max backbone edges): ";
        for (int node : path)
            cout << node << " ";
        cout << endl;
    } else {
        cout << "No path found.\n";
    }

    return 0;
}
