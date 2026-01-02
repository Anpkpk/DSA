#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;
    int burstTime;
    int priority;
    Process(int id, int burstTime, int priority) : id(id), burstTime(burstTime), priority(priority) {} 
};

struct cmp {
    bool operator()(const Process &a, const Process &b) {
        return a.priority < b.priority; 
    }
};

int main() {
    priority_queue<Process, vector<Process>, cmp> process;

    process.push(Process(1, 5, 2));
    process.push(Process(2, 3, 1));
    process.push(Process(3, 8, 3));

    int currentTime = 0;
    double totalWaiting = 0;
    double totalTurnaround = 0;
    int n = process.size();

    while (!process.empty()) {
        Process p = process.top();
        process.pop();

        int waitingTime = currentTime;
        int turnarroundTime = waitingTime + p.burstTime;

        totalWaiting += waitingTime;
        totalTurnaround += turnarroundTime;

        cout << "Id: " << p.id << " " 
             << "waiting time: " << waitingTime << " "
             << "turnaround time: " << turnarroundTime << endl;

        currentTime += p.burstTime;
    }

    cout << "Average time: " << totalWaiting/n << endl;
    cout << "Average turnaround time: " << totalTurnaround/n << endl;
}