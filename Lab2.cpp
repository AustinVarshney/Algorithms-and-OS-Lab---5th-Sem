#include<iostream>
using namespace std;

const int MAX = 100;
const int INF = 100000;

int PrimsAlgo(int graph[MAX][MAX], int n, int stIdx, char verticeProp[]){
    char currChar = verticeProp[stIdx];
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
        if(verticeProp[j]==currChar && graph[stIdx][j] != INF && j != stIdx){
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
            if(verticeProp[j]==currChar && !visited[j] && (idx == -1 || Distance_TV[j] < Distance_TV[idx])){
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
            if(verticeProp[j]==currChar && (Distance_TV[j]>graph[idx][j]) && visited[j] == false){
                Distance_TV[j] = graph[idx][j];
                Nbr_TV[j] = idx;
            }
        }
    }

    // cout<<"Nbr_TV array : ";
    // for(int i=0; i<n; i++){
    //     cout<<Nbr_TV[i]<<" ";
    // }
    // cout<<endl;

    delete[] TE;
    return minLength;
}

int main(){
	int n;
	cout<<"Enter the no. of vertices : ";
	cin>>n;
	int graph[MAX][MAX];
	
    char verticeProp[n];
	for(int i=0; i<n; i++){
        verticeProp[i] = 'D';       //'D' for not having any valid property of the socket
		for(int j=0; j<n; j++){
			graph[i][j] = INF;
		}
    }

    int totalG = 0, totalN = 0, totalL = 0;
    int firstG = -1, firstN = -1, firstL = -1;
	
	while(true){
        int u, v, weight;

        cout<<"Enter 1st Node : ";
        cin>>u;
        if(u == -1) break;
        if(verticeProp[u] == 'D'){
            char prop1;
            cout<<"Enter the Property1 : ";
            cin>>prop1;
            verticeProp[u] = prop1;
            if(prop1 == 'G'){
                totalG++;
                if(totalG == 1){
                    firstG = u;
                };
            } else if(prop1 == 'N'){
                totalN++;
                if(totalN == 1){
                    firstN = u;
                };
            } else if(prop1 == 'L'){
                totalL++;
                if(totalL == 1){
                    firstL = u;
                };
            }
        }

        cout<<"Enter 2nd Node : ";
        cin>>v;
        if(verticeProp[v] == 'D'){
            char prop2;
            cout<<"Enter the Property2 : ";
            cin>>prop2;
            verticeProp[v] = prop2;
            if(prop2 == 'G'){
                totalG++;
                if(totalG == 1){
                    firstG = v;
                };
            } else if(prop2 == 'N'){
                totalN++;
                if(totalN == 1){
                    firstN = v;
                };
            } else if(prop2 == 'L'){
                totalL++;
                if(totalL == 1){
                    firstL = v;
                };
            }
        }

        cout<<"Enter Weight : ";
        cin>>weight;

        graph[u][v] = weight;
        graph[v][u] = weight;
	}

    int minG = PrimsAlgo(graph, n, firstG, verticeProp);
    cout<<"Value of answer1 is : "<<minG<<endl;
    int minN = PrimsAlgo(graph, n, firstN, verticeProp);
    cout<<"Value of answer2 is : "<<minN<<endl; 
    int minL = PrimsAlgo(graph, n, firstL, verticeProp);
    cout<<"Value of answer3 is : "<<minL<<endl;

	return 0;
}