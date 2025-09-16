#include<iostream>
using namespace std;

const int MAX = 100;

struct Node{
    int pid;
    int bt;
public:
    Node(int id, int burstTime){
        pid = id;
        bt = burstTime;
    }
};

class Queue{
    Node* arr[MAX];
    int front = -1, rear = -1;
public:
    void push(Node* el){
        if((rear+1)%MAX == front) {
            return;
        }

        if(front == -1 && rear == -1){
            front = 0; rear = 0;
            arr[rear] = el;
        } else{
            rear = (rear + 1) % MAX;
            arr[rear] = el;
        }
    }

    void pop(){
        if(front == -1){
            return;
        }
        if(front == rear){
            front = -1; rear = -1;
        } else{
            front = (front + 1) % MAX;
        }
    }

    Node* frontEl(){
        if(front == -1) return nullptr;
        return arr[front];
    }

    bool empty(){
        return front == -1;
    }
};

int main(){
    int arrTime[MAX]{0};
    int burstTime[MAX]{0};
    //1
    int originalBurstTime[MAX]{0};  // To store original burst times
    int completionTime[MAX]{0};     // To store completion times
    int waitingTime[MAX]{0};        // To store waiting times
    int turnaroundTime[MAX]{0};     // To store turnaround times

    int n;
    cout<<"Enter how many processes do you want ? ";
    cin>>n;

    int timeRequired = 0;
    for(int i=0; i<n; i++){
        int at, bt;
        cout<<"----------------frontProcess P"<<i+1<<"----------------"<<endl;
        cout<<"Enter Arrival Time : ";
        cin>>at;
        cout<<"Enter Burst Time : ";
        cin>>bt;

        arrTime[i] = at;
        burstTime[i] = bt;
        //1
        originalBurstTime[i] = bt;  // Store original burst time
        timeRequired += bt;
    }

    int quantum;
    cout<<"Enter the value of quantum : ";
    cin>>quantum;

    int time = 0, timeTaken = 0, timeForProcess = 0;
    Queue q;

    cout<<"\n--- Round Robin Execution ---"<<endl;
    while(timeTaken < timeRequired){
        for(int i=0; i<n; i++){
            if(arrTime[i] == time){
                Node* n = new Node(i+1, burstTime[i]);
                q.push(n);
                cout<<"Time "<<time<<": Process P"<<i+1<<" added to queue"<<endl;
            }
        }

        if(!q.empty()){
            Node* frontProcess = q.frontEl();
            cout<<"Time "<<time<<": Running P"<<frontProcess->pid<<" (remaining: "<<frontProcess->bt<<")"<<endl;
            timeTaken++; 
            timeForProcess++;
            frontProcess->bt -= 1;
            time++;

            if(frontProcess->bt == 0){
                cout<<"Time "<<time<<": Process P"<<frontProcess->pid<<" completed"<<endl;
                //1
                completionTime[frontProcess->pid - 1] = time;  // Store completion time
                q.pop();
                delete frontProcess;
                timeForProcess = 0;
            } else if(timeForProcess >= quantum){
                cout<<"Time "<<time<<": Process P"<<frontProcess->pid<<" quantum expired, moved to back"<<endl;
                q.pop();
                q.push(frontProcess);
                timeForProcess = 0;
            }
        } else {
            cout<<"Time "<<time<<": CPU idle"<<endl;
            time++;
        }
    }

    // Calculate Waiting Time and Turnaround Time
    cout<<"\n--- Process Time Calculations ---"<<endl;
    cout<<"Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting"<<endl;
    cout<<"--------------------------------------------------------------"<<endl;
    
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    
    for(int i = 0; i < n; i++){
        turnaroundTime[i] = completionTime[i] - arrTime[i];
        waitingTime[i] = turnaroundTime[i] - originalBurstTime[i];
        
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
        
        cout<<"P"<<i+1<<"\t"<<arrTime[i]<<"\t"<<originalBurstTime[i]<<"\t"
            <<completionTime[i]<<"\t\t"<<turnaroundTime[i]<<"\t\t"<<waitingTime[i]<<endl;
    }
    
    // Calculate and display averages
    double avgWaitingTime = (double)totalWaitingTime / n;
    double avgTurnaroundTime = (double)totalTurnaroundTime / n;
    
    cout<<"\n--- Average Times ---"<<endl;
    cout<<"Average Waiting Time: "<<avgWaitingTime<<" units"<<endl;
    cout<<"Average Turnaround Time: "<<avgTurnaroundTime<<" units"<<endl;

    return 0;
}