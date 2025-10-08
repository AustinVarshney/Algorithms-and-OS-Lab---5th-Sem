#include<iostream>
using namespace std;

const int MAX_PROCESSES = 10;
const int MAX_RESOURCES = 10;
const int MAX_SEQUENCE_LENGTH = 100;

int totalSafeSequences = 0;

bool canAllocate(int available[], int need[][MAX_RESOURCES], int processIndex, int m){
    for(int j=0; j<m; j++){
        if(available[j] < need[processIndex][j]){
            return false;
        }
    }
    return true;
}

void findAllSafeSequences(int available[], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], bool isDone[], char currentSequence[][10], int depth, int n, int m){
    bool allDone = true;
    for(int i=0; i<n; i++){
        if(!isDone[i]){
            allDone = false;
            break;
        }
    }
    
    if(allDone){
        totalSafeSequences++;
        cout<<"Safe Sequence "<<totalSafeSequences<<": ";
        for(int i=0; i<n; i++){
            cout<<currentSequence[i];
            if(i < n-1) cout<<" -> ";
        }
        cout<<endl;
        return;
    }
    
    bool foundProcess = false;
    for(int i=0; i<n; i++){
        if(!isDone[i] && canAllocate(available, need, i, m)){
            foundProcess = true;
            isDone[i] = true;
            
            int savedAvailable[MAX_RESOURCES];
            for(int k=0; k<m; k++){
                savedAvailable[k] = available[k];
            }
            
            for(int k=0; k<m; k++){
                available[k] += allocation[i][k];
            }
            
            currentSequence[depth][0] = 'P';
            int temp = i + 1;
            int idx = 1;
            if(temp >= 10){
                currentSequence[depth][idx++] = '0' + (temp / 10);
                currentSequence[depth][idx++] = '0' + (temp % 10);
            } else {
                currentSequence[depth][idx++] = '0' + temp;
            }
            currentSequence[depth][idx] = '\0';
            
            findAllSafeSequences(available, allocation, need, isDone, currentSequence, depth + 1, n, m);
            isDone[i] = false;
            for(int k=0; k<m; k++){
                available[k] = savedAvailable[k];
            }
        }
    }
}

int main(){
    int m, n;
    cout<<"Enter the no. of resources : ";
    cin>>m;
    cout<<"Enter the no. of processes : ";
    cin>>n;

    int allocation[MAX_PROCESSES][MAX_RESOURCES] = {0};
    int max[MAX_PROCESSES][MAX_RESOURCES] = {0};
    int need[MAX_PROCESSES][MAX_RESOURCES] = {0};
    int available[MAX_RESOURCES] = {0};

    for(int i=0; i<n; i++){
        cout<<"\n----------------Process P"<<i+1<<"----------------"<<endl;
        cout<<"Allocation Matrix:"<<endl;
        for(int j=0; j<m; j++){
            cout<<"Enter allocation of Resource "<<j+1<<": ";
            cin>>allocation[i][j];
        }

        cout<<"\nMax Matrix:"<<endl;
        for(int j=0; j<m; j++){
            cout<<"Enter max of Resource "<<j+1<<": ";
            cin>>max[i][j];
        }
    }

    cout<<"\n================ Available Resources ================"<<endl;
    for(int i=0; i<m; i++){
        cout<<"Enter available Resource "<<i+1<<": ";
        cin>>available[i];
    }
    cout<<endl;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    bool isDone[MAX_PROCESSES] = {false};
    char currentSequence[MAX_PROCESSES][10];
    
    cout<<"================ ALL SAFE SEQUENCES ================"<<endl;    
    findAllSafeSequences(available, allocation, need, isDone, currentSequence, 0, n, m);
    
    if(totalSafeSequences == 0){
        cout<<"System is in UNSAFE state! No safe sequence exists."<<endl;
    } else {
        cout<<"Total number of safe sequences: "<<totalSafeSequences<<endl;
        cout<<"System is in SAFE state!"<<endl;
    }

    return 0;
}