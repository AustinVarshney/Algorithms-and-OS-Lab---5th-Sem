#ifndef SCHEDULINGCORE_H
#define SCHEDULINGCORE_H

#include <vector>
#include <string>
#include <queue>

const int MAX = 100;

// Structure for process information (preserved from your original code)
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

// Node for Round Robin Queue (preserved from your original code)
struct Node{
    int pid;
    int bt;
    
    Node(int id, int burstTime){
        pid = id;
        bt = burstTime;
    }
};

// Queue class for Round Robin (preserved from your original code)
class Queue{
    Node* arr[MAX];
    int front = -1, rear = -1;
    
public:
    void push(Node* el);
    void pop();
    Node* frontEl();
    bool empty();
};

// Structure to hold execution step information for GUI display
struct ExecutionStep {
    int time;
    int processId;
    std::string action;  // "running", "completed", "preempted", "added", "idle"
    int remainingTime;
    
    ExecutionStep(int t, int pid, const std::string& act, int remaining = -1)
        : time(t), processId(pid), action(act), remainingTime(remaining) {}
};

// Main scheduling class that integrates all your algorithms
class CPUScheduler {
private:
    Process processes[MAX];
    int n;
    std::vector<ExecutionStep> executionSteps;
    
public:
    void setProcesses(const std::vector<Process>& procs);
    void roundRobin(int quantum);
    void sjf();
    void srtf();
    
    std::vector<Process> getProcesses() const;
    std::vector<ExecutionStep> getExecutionSteps() const;
    void clearExecutionSteps();
    
    // Calculate average times
    double getAverageWaitingTime() const;
    double getAverageTurnaroundTime() const;
};

#endif // SCHEDULINGCORE_H