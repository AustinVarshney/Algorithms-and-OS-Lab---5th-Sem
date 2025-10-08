#include<iostream>
using namespace std;

const int MAX_PROCESSES = 10;
const int MAX_RESOURCES = 10;

bool waitForGraph[MAX_PROCESSES][MAX_PROCESSES];
bool visited[MAX_PROCESSES];
bool recStack[MAX_PROCESSES];

bool isCyclicUtil(int process, int n){
    visited[process] = true;
    recStack[process] = true;

    // Check all adjacent processes
    for(int i = 0; i < n; i++){
        if(waitForGraph[process][i]){
            if(!visited[i]){
                if(isCyclicUtil(i, n)){
                    return true;
                }
            } else if(recStack[i]){
                return true;
            }
        }
    }

    recStack[process] = false;
    return false;
}

bool detectCycle(int n){
    for(int i = 0; i < n; i++){
        visited[i] = false;
        recStack[i] = false;
    }

    for(int i = 0; i < n; i++){
        if(!visited[i]){
            if(isCyclicUtil(i, n)){
                return true;
            }
        }
    }
    return false;
}

// Function to print the cycle path (if exists)
void printCyclePath(int start, int current, bool pathVisited[], char path[][10], int depth, int n){
    pathVisited[current] = true;
    
    // Add current process to path
    path[depth][0] = 'P';
    int temp = current + 1;
    int idx = 1;
    if(temp >= 10){
        path[depth][idx++] = '0' + (temp / 10);
        path[depth][idx++] = '0' + (temp % 10);
    } else{
        path[depth][idx++] = '0' + temp;
    }
    path[depth][idx] = '\0';

    // Check if we found a cycle
    if(current == start && depth > 0){
        cout<<"Cycle detected: ";
        for(int i = 0; i <= depth; i++){
            cout<<path[i];
            if(i < depth) cout<<" -> ";
        }
        cout<<endl;
        return;
    }

    // Continue exploring
    for(int i = 0; i < n; i++){
        if(waitForGraph[current][i]){
            if(i == start || !pathVisited[i]){
                printCyclePath(start, i, pathVisited, path, depth + 1, n);
            }
        }
    }
    
    pathVisited[current] = false;  // Backtrack
}

int main(){
    int n, m;
    cout<<"Enter the number of processes: ";
    cin>>n;
    cout<<"Enter the number of resources: ";
    cin>>m;

    int allocation[MAX_PROCESSES][MAX_RESOURCES] ={0};
    int request[MAX_PROCESSES][MAX_RESOURCES] ={0};

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            waitForGraph[i][j] = false;
        }
    }

    cout<<"\n================ Resource Allocation ================"<<endl;
    cout<<"(Enter 1 if process holds the resource, 0 otherwise)"<<endl;
    for(int i = 0; i < n; i++){
        cout<<"Process P"<<i+1<<":"<<endl;
        for(int j = 0; j < m; j++){
            cout<<"  Does P"<<i+1<<" hold Resource R"<<j+1<<"? (1/0): ";
            cin>>allocation[i][j];
        }
        cout<<endl;
    }
    cout<<endl;

    cout<<"================ Resource Requests ================"<<endl;
    cout<<"(Enter 1 if process is requesting the resource, 0 otherwise)"<<endl;
    for(int i = 0; i < n; i++){
        cout<<"Process P"<<i+1<<":"<<endl;
        for(int j = 0; j < m; j++){
            cout<<"  Is P"<<i+1<<" requesting Resource R"<<j+1<<"? (1/0): ";
            cin>>request[i][j];
        }
        cout<<endl;
    }
    cout<<endl;

    cout<<"================ BUILDING WAIT-FOR GRAPH ================"<<endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(request[i][j] == 1){
                for(int k = 0; k < n; k++){
                    if(k != i && allocation[k][j] == 1){
                        waitForGraph[i][k] = true;
                        cout<<"P"<<i+1<<" is waiting for P"<<k+1<<" (Resource R"<<j+1<<")"<<endl;
                    }
                }
            }
        }
    }

    bool hasEdges = false;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(waitForGraph[i][j]){
                // cout<<"P"<<i+1<<" -> P"<<j+1<<endl;
                hasEdges = true;
            }
        }
    }
    if(!hasEdges){
        cout<<"No edges in the graph (No process is waiting)"<<endl;
    }

    bool hasCycle = detectCycle(n);
    
    if(hasCycle){
        cout<<"DEADLOCK DETECTED!"<<endl;
        cout<<"\nFinding cycle path(s)..."<<endl;
        
        // Print cycle paths
        for(int i = 0; i < n; i++){
            bool pathVisited[MAX_PROCESSES] ={false};
            char path[MAX_PROCESSES][10];
            
            // Check if this process is part of a cycle
            for(int j = 0; j < n; j++){
                if(waitForGraph[i][j]){
                    bool tempVisited[MAX_PROCESSES] ={false};
                    bool tempRecStack[MAX_PROCESSES] ={false};
                    
                    // Use temporary arrays for checking
                    for(int k = 0; k < n; k++){
                        visited[k] = false;
                        recStack[k] = false;
                    }
                    
                    if(isCyclicUtil(i, n) && recStack[i]){
                        printCyclePath(i, i, pathVisited, path, 0, n);
                        break;
                    }
                }
            }
        }
        
        cout<<"System is in DEADLOCK state!"<<endl;
    } else{
        cout<<"NO DEADLOCK DETECTED"<<endl;
        cout<<"System is in SAFE state!"<<endl;
    }

    return 0;
}