#include "schedulingcore.h"
#include <algorithm>

// Queue implementation (preserved from your original code)
void Queue::push(Node* el) {
    if((rear+1)%MAX == front) return;

    if(front == -1 && rear == -1){
        front = 0; rear = 0;
        arr[rear] = el;
    } else{
        rear = (rear + 1) % MAX;
        arr[rear] = el;
    }
}

void Queue::pop() {
    if(front == -1) return;
    if(front == rear){
        front = -1; rear = -1;
    } else{
        front = (front + 1) % MAX;
    }
}

Node* Queue::frontEl() {
    if(front == -1) return nullptr;
    return arr[front];
}

bool Queue::empty() {
    return front == -1;
}

// CPUScheduler implementation
void CPUScheduler::setProcesses(const std::vector<Process>& procs) {
    n = procs.size();
    for(int i = 0; i < n && i < MAX; i++) {
        processes[i] = procs[i];
        processes[i].pid = i + 1;
        processes[i].originalBurstTime = procs[i].burstTime;
    }
    clearExecutionSteps();
}

void CPUScheduler::clearExecutionSteps() {
    executionSteps.clear();
}

// Round Robin implementation (adapted from your original code)
void CPUScheduler::roundRobin(int quantum) {
    // Reset burst times
    for(int i = 0; i < n; i++) {
        processes[i].burstTime = processes[i].originalBurstTime;
        processes[i].completionTime = 0;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
    }
    
    clearExecutionSteps();
    
    int time = 0, completed = 0, timeForProcess = 0;
    Queue q;
    
    // Calculate total time required
    int totalTime = 0;
    for(int i = 0; i < n; i++) totalTime += processes[i].originalBurstTime;
    
    while(completed < n) {
        // Add processes that arrive at current time
        for(int i = 0; i < n; i++) {
            if(processes[i].arrivalTime == time && processes[i].burstTime > 0) {
                Node* newNode = new Node(i, processes[i].burstTime);
                q.push(newNode);
                executionSteps.push_back(ExecutionStep(time, i+1, "added"));
            }
        }
        
        if(!q.empty()) {
            Node* current = q.frontEl();
            int processIndex = current->pid;
            
            executionSteps.push_back(ExecutionStep(time, processIndex+1, "running", current->bt));
            
            current->bt--;
            processes[processIndex].burstTime--;
            timeForProcess++;
            time++;
            
            if(current->bt == 0) {
                executionSteps.push_back(ExecutionStep(time, processIndex+1, "completed"));
                processes[processIndex].completionTime = time;
                completed++;
                q.pop();
                delete current;
                timeForProcess = 0;
            } else if(timeForProcess >= quantum) {
                executionSteps.push_back(ExecutionStep(time, processIndex+1, "preempted", current->bt));
                q.pop();
                q.push(current);
                timeForProcess = 0;
            }
        } else {
            executionSteps.push_back(ExecutionStep(time, -1, "idle"));
            time++;
        }
    }
    
    // Calculate times
    for(int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].originalBurstTime;
    }
}

// SJF implementation (adapted from your original code)
void CPUScheduler::sjf() {
    // Reset burst times
    for(int i = 0; i < n; i++) {
        processes[i].burstTime = processes[i].originalBurstTime;
        processes[i].completionTime = 0;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
    }
    
    clearExecutionSteps();
    
    int time = 0, completed = 0;
    
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
            executionSteps.push_back(ExecutionStep(time, -1, "idle"));
            time++;
        } else {
            executionSteps.push_back(ExecutionStep(time, shortestJob+1, "running", processes[shortestJob].burstTime));
            
            time += processes[shortestJob].burstTime;
            processes[shortestJob].completionTime = time;
            processes[shortestJob].burstTime = 0;
            completed++;
            
            executionSteps.push_back(ExecutionStep(time, shortestJob+1, "completed"));
        }
    }
    
    // Calculate times
    for(int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].originalBurstTime;
    }
}

// SRTF implementation (adapted from your original code)
void CPUScheduler::srtf() {
    // Reset burst times
    for(int i = 0; i < n; i++) {
        processes[i].burstTime = processes[i].originalBurstTime;
        processes[i].completionTime = 0;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
    }
    
    clearExecutionSteps();
    
    int time = 0, completed = 0, currentProcess = -1;
    int totalTime = 0;
    for(int i = 0; i < n; i++) totalTime += processes[i].originalBurstTime;
    
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
            executionSteps.push_back(ExecutionStep(time, -1, "idle"));
            time++;
        } else {
            // Check for process switch
            if(currentProcess != shortestRemaining) {
                if(currentProcess != -1) {
                    executionSteps.push_back(ExecutionStep(time, currentProcess+1, "preempted", processes[currentProcess].burstTime));
                }
                executionSteps.push_back(ExecutionStep(time, shortestRemaining+1, "running", processes[shortestRemaining].burstTime));
                currentProcess = shortestRemaining;
            }
            
            processes[shortestRemaining].burstTime--;
            time++;
            
            if(processes[shortestRemaining].burstTime == 0) {
                processes[shortestRemaining].completionTime = time;
                executionSteps.push_back(ExecutionStep(time, shortestRemaining+1, "completed"));
                completed++;
                currentProcess = -1;
            }
        }
    }
    
    // Calculate times
    for(int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].originalBurstTime;
    }
}

std::vector<Process> CPUScheduler::getProcesses() const {
    std::vector<Process> result;
    for(int i = 0; i < n; i++) {
        result.push_back(processes[i]);
    }
    return result;
}

std::vector<ExecutionStep> CPUScheduler::getExecutionSteps() const {
    return executionSteps;
}

double CPUScheduler::getAverageWaitingTime() const {
    double total = 0;
    for(int i = 0; i < n; i++) {
        total += processes[i].waitingTime;
    }
    return n > 0 ? total / n : 0;
}

double CPUScheduler::getAverageTurnaroundTime() const {
    double total = 0;
    for(int i = 0; i < n; i++) {
        total += processes[i].turnaroundTime;
    }
    return n > 0 ? total / n : 0;
}