#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

const int MAXN = 100;    // Change as per maximum nodes
const int MAXDEG = 100;  // Max degree per node

struct Edge {
    int to;
    bool isBackbone;
};

// Adjacency list using arrays
struct AdjList {
    Edge edges[MAXDEG];
    int count = 0;  // how many edges are stored
};

int findPreferredPath(int n, int source, int dest, AdjList graph[], int path[]) {
    int dist[MAXN];
    int parent[MAXN];
    deque<int> dq;

    for(int i = 0; i < n; i++){
        dist[i] = INT8_MAX;
        parent[i] = -1;
    }

    dist[source] = 0;
    dq.push_front(source);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        for (int idx = 0; idx < graph[u].count; idx++) {
            Edge &edge = graph[u].edges[idx];
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

    // Reconstruct path into the provided array "path"
    if (dist[dest] == INT8_MAX) return 0; // no path

    int len = 0;
    for (int at = dest; at != -1; at = parent[at])
        path[len++] = at;

    reverse(path, path + len);
    return len;
}

int main() {
    int n = 5;
    AdjList graph[MAXN];

    // Build graph
    graph[0].edges[graph[0].count++] = {1, true};
    graph[1].edges[graph[1].count++] = {0, true};

    graph[2].edges[graph[2].count++] = {1, true};
    graph[1].edges[graph[1].count++] = {2, true};

    graph[2].edges[graph[2].count++] = {3, true};
    graph[3].edges[graph[3].count++] = {2, true};

    graph[4].edges[graph[4].count++] = {3, true};
    graph[3].edges[graph[3].count++] = {4, true};

    graph[4].edges[graph[4].count++] = {0, false};
    graph[0].edges[graph[0].count++] = {4, false};

    int source = 0, destination = 4;

    int path[MAXN];
    int length = findPreferredPath(n, source, destination, graph, path);

    if (length > 0) {
        cout << "Preferred path (max backbone edges): ";
        for (int i = 0; i < length; i++)
            cout << path[i] << " ";
        cout << endl;
    } else {
        cout << "No path found.\n";
    }

    return 0;
}
