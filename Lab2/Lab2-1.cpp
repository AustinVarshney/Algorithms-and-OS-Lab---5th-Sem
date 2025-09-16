#include<iostream>
using namespace std;

const int MAX = 100;
const int INF = 100000;

int PrimsAlgo(int graph[MAX][MAX], int n, int stIdx, int verticeProp[], bool filterByGround){
    bool visited[n]{false};
    int minLength = 0;

    int Distance_TV[n];
    int Nbr_TV[n];
    for(int i=0; i<n; i++){
        Distance_TV[i] = INF;
        Nbr_TV[i] = -1;
    }

    int* TE = nullptr;
    int oldSize = 0;

    for(int j=0; j<n; j++){
        bool includeNode = (filterByGround) ? (verticeProp[j] == 1) : true;
        if(includeNode && graph[stIdx][j] != INF && j != stIdx){
            Nbr_TV[j] = stIdx;
            Distance_TV[j] = graph[stIdx][j];
        } 
    }

    Distance_TV[stIdx] = 0;
    Nbr_TV[stIdx] = -1;
    visited[stIdx] = true;

    for(int i=1; i<n; i++){
        int idx = -1;
        for(int j=0; j<n; j++){
            bool includeNode = (filterByGround) ? (verticeProp[j] == 1) : true;
            if(includeNode && !visited[j] && (idx == -1 || Distance_TV[j] < Distance_TV[idx])){
                idx = j;
            }
        }
        if (idx == -1) break;

        visited[idx] = true;

        int newSize = oldSize + 1;
        int* newArr = new int[newSize];
        for (int i = 0; i < oldSize; ++i)
            newArr[i] = TE[i];

        newArr[newSize - 1] = graph[idx][Nbr_TV[idx]];
        minLength += graph[idx][Nbr_TV[idx]];
        cout<<idx<<" - "<<Nbr_TV[idx]<<" -> "<<graph[idx][Nbr_TV[idx]]<<endl;
        delete[] TE;
        TE = newArr;
        oldSize = newSize;

        for(int j=0; j<n; j++){
            bool includeNode = (filterByGround) ? (verticeProp[j] == 1) : true;
            if(includeNode && (Distance_TV[j]>graph[idx][j]) && visited[j] == false){
                Distance_TV[j] = graph[idx][j];
                Nbr_TV[j] = idx;
            }
        }
    }

    delete[] TE;
    return minLength;
}

int main(){
	int n;
	cout<<"Enter the no. of vertices : ";
	cin>>n;
	int graph[MAX][MAX];
	
    int verticeProp[n];
	for(int i=0; i<n; i++){
        verticeProp[i] = -1;
		for(int j=0; j<n; j++){
			graph[i][j] = INF;
		}
    }

    int totalG = 0, totalN = 0, totalL = 0;
    int firstG = 0;
	
	while(true){
        int u, v, weight;

        cout<<"Enter 1st Node : ";
        cin>>u;
        if(u == -1) break;
        if(verticeProp[u] == -1){
            int isHavingGround;
            cout<<"Enter 1 if grounded or 0 : ";
            cin>>isHavingGround;
            verticeProp[u] = isHavingGround;
            if(isHavingGround == 1){
                totalG++;
                if(totalG == 1){
                    firstG = u;
                };
            }
        }

        cout<<"Enter 2nd Node : ";
        cin>>v;
        if(verticeProp[v] == -1){
            int isHavingGround;
            cout<<"Enter 1 if grounded or 0 : ";
            cin>>isHavingGround;
            verticeProp[v] = isHavingGround;
            if(isHavingGround == 1){
                totalG++;
                if(totalG == 1){
                    firstG = v;
                };
            }
        }

        cout<<"Enter Weight : ";
        cin>>weight;

        graph[u][v] = weight;
        graph[v][u] = weight;
	}

    int minG = PrimsAlgo(graph, n, firstG, verticeProp, true);
    cout<<"Value of answer1 is : "<<minG<<endl;
    int minN = PrimsAlgo(graph, n, 0, verticeProp, false);
    cout<<"Value of answer2 is : "<<minN<<endl; 
    int minL = PrimsAlgo(graph, n, 0, verticeProp, false);
    cout<<"Value of answer3 is : "<<minL<<endl;

	return 0;
}