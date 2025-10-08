#include<iostream>
#include<string>
using namespace std;

struct Node{
    int* arr;
    int size;

    Node(){
        arr = nullptr;
        size = 0;
    }

    Node(int s){
        size = s;
        arr = new int[size];
        for(int i=0; i<size; i++){
            arr[i] = 0;
        }
    }

    Node(const Node& other){
        size = other.size;
        arr = new int[size];
        for(int i=0; i<size; i++){
            arr[i] = other.arr[i];
        }
    }

    Node& operator=(const Node& other){
        if(this != &other){
            delete[] arr;
            size = other.size;
            arr = new int[size];
            for(int i=0; i<size; i++){
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    ~Node(){
        delete[] arr;
    }
};

int findNode(Node& available, Node need[], bool isDone[], int n, int m){
    for(int i=0; i<n; i++){
        if(!isDone[i]){
            bool canAllocate = true;
            for(int j=0; j<m; j++){
                if(available.arr[j] < need[i].arr[j]){
                    canAllocate = false;
                    break;
                }
            }
            if(canAllocate){
                return i;
            }
        }
    }
    return -1;
}

int main(){
    int m, n;
    cout<<"Enter the no. of resources : ";
    cin>>m;
    cout<<"Enter the no. of processes : ";
    cin>>n;

    Node allocation[n];
    Node max[n];
    Node need[n];
    
    for(int i=0; i<n; i++){
        allocation[i] = Node(m);
        max[i] = Node(m);
        need[i] = Node(m);
    }

    for(int i=0; i<n; i++){
        cout<<"\n----------------Process P"<<i+1<<"----------------"<<endl;
        cout<<"Allocation Matrix:"<<endl;
        for(int j=0; j<m; j++){
            cout<<"Enter the value of allocation of Resource "<<j+1<<": ";
            cin>>allocation[i].arr[j];
        }

        cout<<"\nMax Matrix:"<<endl;
        for(int j=0; j<m; j++){
            cout<<"Enter the value of max of Resource "<<j+1<<" needed: ";
            cin>>max[i].arr[j];
        }
    }

    Node available(m);
    cout<<"\n================ Available Resources ================"<<endl;
    for(int i=0; i<m; i++){
        cout<<"Enter available Resource "<<i+1<<": ";
        cin>>available.arr[i];
    }
    cout<<endl<<endl;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            need[i].arr[j] = max[i].arr[j] - allocation[i].arr[j];
        }
    }

    bool isDone[n];
    for(int i=0; i<n; i++) isDone[i] = false;
    
    string safeSequence[n];
    bool isSystemSafe = true;

    for(int i=0; i<n; i++){
        int j = findNode(available, need, isDone, n, m);
        
        if(j == -1){
            cout<<"System is in UNSAFE state!"<<endl;
            isSystemSafe = false;
            break;
        }

        for(int k=0; k<m; k++){
            available.arr[k] += allocation[j].arr[k];
        }

        isDone[j] = true;
        safeSequence[i] = "P" + to_string(j+1);
    }

    if(isSystemSafe){
        cout<<"System is in SAFE state!"<<endl;
        cout<<"Safe Sequence: ";
        for(int i=0; i<n; i++){
            cout<<safeSequence[i];
            if(i < n-1) cout<<" -> ";
        }
        cout<<endl;
    }

    return 0;
}