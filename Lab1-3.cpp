#include<iostream>
using namespace std;

const int MAX = 100;
const int INF = 10000;

void findPath(int n, int src, int dest, int graph[100][100]){
    int dist[n];
    int par[n];
    bool visited[n];

    for(int i=0; i<n; i++){
        dist[i] = INF;
        par[i] = -1;
        visited[i] = false;
    }

    dist[src] = 0;

    for(int i=0; i<n-1; i++){
        int u=-1;
        int minDist = INF;

        for(int v=0; v<n; v++){
            if(!visited[v] && dist[v] < minDist){
                minDist = dist[v];
                u = v;
            }
        }

        if(u == -1) break;

        visited[u] = true;

        for(int j=0; j<n; j++){
            if(!visited[j] && graph[u][j] != INF){
                if(dist[u] + graph[u][j] < dist[j]){
                    dist[j] = dist[u] + graph[u][j];
                    par[j] = u;
                }
            }
        }
    }

    int len = 0;
    int ans[n];
    for(int i=dest; i!=-1; i = par[i]){
        ans[len++] = i;
    }

    int st = 0, end = len-1;
    while(st <= end){
        swap(ans[st++], ans[end--]);
    }

    for(int i=0; i<len; i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
}


int main(){
    int n = 6;    
    int graph[MAX][MAX];

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            graph[i][j] = INF;
        }
    }

    graph[0][1] = 0;
    graph[1][0] = 0;

    graph[2][0] = 0;
    graph[0][2] = 0;

    graph[5][0] = 0;
    graph[0][5] = 0;

    graph[2][3] = 0;
    graph[3][2] = 0;

    graph[3][4] = 0;
    graph[4][3] = 0;

    graph[4][5] = 0;
    graph[5][4] = 0;

    int src = 2, dest = 5;
    findPath(n, src, dest, graph);

    return 0;
}