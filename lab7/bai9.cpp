#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;
    int burstTime;
    int priority;
    int arrivalTime;
    Process(int id, int burstTime, int priority, int arrivalTime) : 
        id(id), burstTime(burstTime), priority(priority), arrivalTime(arrivalTime) {} 
};

struct cmp {
    bool operator()(const Process &a, const Process &b) {
        return a.priority < b.priority; 
    }
};

bool cmp_arrival(const Process &a, const Process &b) {
    return a.arrivalTime > b.arrivalTime;
}

int main() {
    vector<Process> p = {
        {1, 0, 5, 2},
        {2, 1, 3, 1},
        {3, 2, 8, 3},
        {4, 4, 6, 2}
    };

    sort(p.begin(), p.end(), cmp_arrival);

    priority_queue<Process, vector<Process>, cmp> process;

    int currentTime = 0;
    int idx = 0;
    int n = p.size();

    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;

    cout << "ID\tAT\tBT\tWT\tTAT\n";

    while (idx < n or !process.empty()) {
        while (idx < n and p[idx].arrivalTime <= currentTime) {
            process.push(p[idx]);
            idx++;
        }

        if (!process.empty()) {
            Process cur = process.top();
            process.pop();

            int waitingTime = currentTime - cur.arrivalTime;
            int turnaroundTime = waitingTime + cur.burstTime;

            totalWaitingTime += waitingTime;
            totalTurnaroundTime += turnaroundTime;
            
            cout << cur.id << "\t"
                 << cur.arrivalTime << "\t"
                 << cur.burstTime << "\t"
                 << waitingTime << "\t"
                 << turnaroundTime << endl;

            currentTime += cur.burstTime;
        }
        else 
            currentTime = p[idx].arrivalTime;
    }

    cout << "Average Waiting Time = " << totalWaitingTime/n << endl;
    cout << "Average Turnaround Time = " << totalTurnaroundTime/n << endl;
}

