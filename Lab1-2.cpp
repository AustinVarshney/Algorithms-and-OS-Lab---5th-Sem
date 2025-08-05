#include<iostream>
using namespace std;

const int MAXN = 100;

struct Edge{
    int to;
    bool isBackbone;
};

struct AdjList{
    Edge edges[MAXN];
    int count = 0;
};

struct ArrayDeque{
    int data[2*MAXN];
    int head = MAXN;
    int tail = MAXN;

    bool empty(){
        return head == tail;
    }

    void push_front(int val){
        head--;
        data[head] = val;
    }

    void push_back(int val){
        tail++;
        data[tail] = val;
    }

    int pop_front(){
        int front = data[head];
        head++;
        return front;
    }
};

int findPreferredPath(int n, int source, int dest, AdjList graph[], int path[]){
    int dist[MAXN];
    int parent[MAXN];
    ArrayDeque dq;

    for (int i = 0; i < n; i++){
        dist[i] = INT8_MAX;
        parent[i] = -1;
    }

    dist[source] = 0;
    dq.push_front(source);

    while (!dq.empty()){
        int u = dq.pop_front();

        for (int idx = 0; idx < graph[u].count; idx++){
            Edge &edge = graph[u].edges[idx];
            int v = edge.to;
            int weight = edge.isBackbone ? 0 : 1;

            if (dist[u] + weight < dist[v]){
                dist[v] = dist[u] + weight;
                parent[v] = u;

                if (weight == 0)
                    dq.push_front(v);
                else
                    dq.push_back(v);
            }
        }
    }

    int len = 0;
    for (int at = dest; at != -1; at = parent[at])
        path[len++] = at;

    int st = 0, end = len-1;
    while(st <= end){
        int temp = path[st];
        path[st] = path[end];
        path[end] = temp;
        st++;
        end--;
    }

    return len;
}

int main(){
    int n = 6;
    AdjList graph[MAXN];

    graph[0].edges[graph[0].count++] = {1, false};
    graph[1].edges[graph[1].count++] = {0, false};

    graph[0].edges[graph[0].count++] = {4, false};
    graph[4].edges[graph[4].count++] = {0, false};
    
    graph[0].edges[graph[0].count++] = {5, false};
    graph[5].edges[graph[5].count++] = {0, false};

    graph[2].edges[graph[2].count++] = {1, false};
    graph[1].edges[graph[1].count++] = {2, false};

    graph[3].edges[graph[3].count++] = {1, true};
    graph[1].edges[graph[1].count++] = {3, true};

    graph[2].edges[graph[2].count++] = {3, true};
    graph[3].edges[graph[3].count++] = {2, true};

    graph[4].edges[graph[4].count++] = {3, true};
    graph[3].edges[graph[3].count++] = {4, true};

    graph[4].edges[graph[4].count++] = {5, true};
    graph[5].edges[graph[5].count++] = {4, true};

    int source = 0, destination = 2;

    int path[MAXN];
    int length = findPreferredPath(n, source, destination, graph, path);

    cout << "Preferred path (max backbone edges): ";
    for (int i = 0; i < length; i++)
        cout << path[i] << " ";
    cout << endl;

    return 0;
}
