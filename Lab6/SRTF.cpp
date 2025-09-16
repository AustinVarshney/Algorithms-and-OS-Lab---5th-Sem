#include<iostream>
using namespace std;

const int MAX = 100;

int main(){
    int arrTime[MAX]{0};
    int burstTime[MAX]{0};
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
        cout<<"----------------PROCESS P"<<i+1<<"----------------"<<endl;
        cout<<"Enter Arrival Time : ";
        cin>>at;
        cout<<"Enter Burst Time : ";
        cin>>bt;

        arrTime[i] = at;
        burstTime[i] = bt;
        originalBurstTime[i] = bt;  // Store original burst time
        timeRequired += bt;
    }

    int time = 0, timeTaken = 0;
    int currentProcess = -1;
    
    cout<<"\n--- SRTF (Preemptive SJF) Execution ---"<<endl;
    
    while(timeTaken < timeRequired){
        int minProcessIdx = -1;
    
        // Find process with shortest remaining time among arrived processes
        for(int i=0; i<n; i++){
            if(arrTime[i] <= time && burstTime[i] > 0){
                if(minProcessIdx == -1 || burstTime[i] < burstTime[minProcessIdx]){
                    minProcessIdx = i;
                }
            }
        }

        if(minProcessIdx == -1){
            cout<<"Time "<<time<<": CPU idle"<<endl;
            time++;
        } else{
            // Check if we're switching to a different process
            if(currentProcess != minProcessIdx){
                if(currentProcess != -1){
                    cout<<"Time "<<time<<": Process P"<<currentProcess+1<<" preempted (remaining: "<<burstTime[currentProcess]<<")"<<endl;
                }
                cout<<"Time "<<time<<": Running P"<<minProcessIdx+1<<" (remaining: "<<burstTime[minProcessIdx]<<")"<<endl;
                currentProcess = minProcessIdx;
            }
            
            // Execute for 1 time unit
            burstTime[minProcessIdx]--;
            timeTaken++;
            time++;
            
            // Check if process completed
            if(burstTime[minProcessIdx] == 0){
                completionTime[minProcessIdx] = time;  // Store completion time
                cout<<"Time "<<time<<": Process P"<<minProcessIdx+1<<" completed"<<endl;
                currentProcess = -1;
            }
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