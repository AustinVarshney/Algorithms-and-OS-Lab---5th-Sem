#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

const int MAX = 100;

// Structure for process information
struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int originalBurstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    
    Process() : pid(0), arrivalTime(0), burstTime(0), originalBurstTime(0), 
                completionTime(0), waitingTime(0), turnaroundTime(0) {}
};

// Node for Round Robin Queue
struct Node{
    int pid;
    int bt;
    
    Node(int id, int burstTime){
        pid = id;
        bt = burstTime;
    }
};

// Queue class for Round Robin
class Queue{
    Node* arr[MAX];
    int front = -1, rear = -1;
    
public:
    void push(Node* el){
        if((rear+1)%MAX == front) return;

        if(front == -1 && rear == -1){
            front = 0; rear = 0;
            arr[rear] = el;
        } else{
            rear = (rear + 1) % MAX;
            arr[rear] = el;
        }
    }

    void pop(){
        if(front == -1) return;
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

class CPUScheduler {
private:
    Process processes[MAX];
    int n;
    
public:
    void inputProcesses() {
        cout << "Enter number of processes: ";
        cin >> n;
        
        for(int i = 0; i < n; i++) {
            cout << "---------------- Process P" << i+1 << " ----------------" << endl;
            cout << "Enter Arrival Time: ";
            cin >> processes[i].arrivalTime;
            cout << "Enter Burst Time: ";
            cin >> processes[i].burstTime;
            
            processes[i].pid = i + 1;
            processes[i].originalBurstTime = processes[i].burstTime;
        }
    }
    
    void displayResults() {
        cout << "\n--- Process Time Calculations ---" << endl;
        cout << left << setw(8) << "Process" << setw(8) << "Arrival" << setw(8) << "Burst" 
             << setw(12) << "Completion" << setw(12) << "Turnaround" << setw(8) << "Waiting" << endl;
        cout << string(60, '-') << endl;
        
        int totalWaiting = 0, totalTurnaround = 0;
        
        for(int i = 0; i < n; i++) {
            processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
            processes[i].waitingTime = processes[i].turnaroundTime - processes[i].originalBurstTime;
            
            totalWaiting += processes[i].waitingTime;
            totalTurnaround += processes[i].turnaroundTime;
            
            cout << left << setw(8) << ("P" + to_string(processes[i].pid))
                 << setw(8) << processes[i].arrivalTime
                 << setw(8) << processes[i].originalBurstTime
                 << setw(12) << processes[i].completionTime
                 << setw(12) << processes[i].turnaroundTime
                 << setw(8) << processes[i].waitingTime << endl;
        }
        
        cout << "\n--- Average Times ---" << endl;
        cout << fixed << setprecision(2);
        cout << "Average Waiting Time: " << (double)totalWaiting / n << " units" << endl;
        cout << "Average Turnaround Time: " << (double)totalTurnaround / n << " units" << endl;
    }
    
    void roundRobin() {
        // Reset burst times
        for(int i = 0; i < n; i++) {
            processes[i].burstTime = processes[i].originalBurstTime;
        }
        
        int quantum;
        cout << "Enter time quantum: ";
        cin >> quantum;
        
        int time = 0, completed = 0, timeForProcess = 0;
        Queue q;
        
        cout << "\n--- Round Robin Execution ---" << endl;
        
        // Calculate total time required
        int totalTime = 0;
        for(int i = 0; i < n; i++) totalTime += processes[i].originalBurstTime;
        
        while(completed < n) {
            // Add processes that arrive at current time
            for(int i = 0; i < n; i++) {
                if(processes[i].arrivalTime == time && processes[i].burstTime > 0) {
                    Node* newNode = new Node(i, processes[i].burstTime);
                    q.push(newNode);
                    cout << "Time " << time << ": Process P" << i+1 << " added to queue" << endl;
                }
            }
            
            if(!q.empty()) {
                Node* current = q.frontEl();
                int processIndex = current->pid;
                
                cout << "Time " << time << ": Running P" << processIndex+1 
                     << " (remaining: " << current->bt << ")" << endl;
                
                current->bt--;
                processes[processIndex].burstTime--;
                timeForProcess++;
                time++;
                
                if(current->bt == 0) {
                    cout << "Time " << time << ": Process P" << processIndex+1 << " completed" << endl;
                    processes[processIndex].completionTime = time;
                    completed++;
                    q.pop();
                    delete current;
                    timeForProcess = 0;
                } else if(timeForProcess >= quantum) {
                    cout << "Time " << time << ": Process P" << processIndex+1 
                         << " quantum expired, moved to back" << endl;
                    q.pop();
                    q.push(current);
                    timeForProcess = 0;
                }
            } else {
                cout << "Time " << time << ": CPU idle" << endl;
                time++;
            }
        }
    }
    
    void sjf() {
        // Reset burst times
        for(int i = 0; i < n; i++) {
            processes[i].burstTime = processes[i].originalBurstTime;
        }
        
        int time = 0, completed = 0;
        
        cout << "\n--- SJF Execution ---" << endl;
        
        while(completed < n) {
            int shortestJob = -1;
            
            // Find shortest job among arrived processes
            for(int i = 0; i < n; i++) {
                if(processes[i].arrivalTime <= time && processes[i].burstTime > 0) {
                    if(shortestJob == -1 || processes[i].burstTime < processes[shortestJob].burstTime) {
                        shortestJob = i;
                    }
                }
            }
            
            if(shortestJob == -1) {
                time++;
            } else {
                cout << "Time " << time << ": Running P" << shortestJob+1 
                     << " (burst: " << processes[shortestJob].burstTime << ")" << endl;
                
                time += processes[shortestJob].burstTime;
                processes[shortestJob].completionTime = time;
                processes[shortestJob].burstTime = 0;
                completed++;
                
                cout << "Time " << time << ": Process P" << shortestJob+1 << " completed" << endl;
            }
        }
    }
    
    void srtf() {
        // Reset burst times
        for(int i = 0; i < n; i++) {
            processes[i].burstTime = processes[i].originalBurstTime;
        }
        
        int time = 0, completed = 0, currentProcess = -1;
        
        cout << "\n--- SRTF Execution ---" << endl;
        
        while(completed < n) {
            int shortestRemaining = -1;
            
            // Find process with shortest remaining time
            for(int i = 0; i < n; i++) {
                if(processes[i].arrivalTime <= time && processes[i].burstTime > 0) {
                    if(shortestRemaining == -1 || processes[i].burstTime < processes[shortestRemaining].burstTime) {
                        shortestRemaining = i;
                    }
                }
            }
            
            if(shortestRemaining == -1) {
                cout << "Time " << time << ": CPU idle" << endl;
                time++;
            } else {
                // Check for process switch
                if(currentProcess != shortestRemaining) {
                    if(currentProcess != -1) {
                        cout << "Time " << time << ": Process P" << currentProcess+1 
                             << " preempted (remaining: " << processes[currentProcess].burstTime << ")" << endl;
                    }
                    cout << "Time " << time << ": Running P" << shortestRemaining+1 
                         << " (remaining: " << processes[shortestRemaining].burstTime << ")" << endl;
                    currentProcess = shortestRemaining;
                }
                
                processes[shortestRemaining].burstTime--;
                time++;
                
                if(processes[shortestRemaining].burstTime == 0) {
                    processes[shortestRemaining].completionTime = time;
                    cout << "Time " << time << ": Process P" << shortestRemaining+1 << " completed" << endl;
                    completed++;
                    currentProcess = -1;
                }
            }
        }
    }
};

int main() {
    CPUScheduler scheduler;
    int choice;
    
    cout << "=== CPU SCHEDULING ALGORITHMS ===" << endl;
    cout << "1. Round Robin (RR)" << endl;
    cout << "2. Shortest Job First (SJF)" << endl;
    cout << "3. Shortest Remaining Time First (SRTF)" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> choice;
    
    scheduler.inputProcesses();
    
    switch(choice) {
        case 1:
            scheduler.roundRobin();
            break;
        case 2:
            scheduler.sjf();
            break;
        case 3:
            scheduler.srtf();
            break;
        default:
            cout << "Invalid choice!" << endl;
            return 1;
    }
    
    scheduler.displayResults();
    
    return 0;
}