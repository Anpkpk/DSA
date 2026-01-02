#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    Process(int id, int arrivalTime, int burstTime, int priority) : 
        id(id), burstTime(burstTime), priority(priority), arrivalTime(arrivalTime) {} 
};

struct cmp {
    bool operator()(const Process &a, const Process &b) {
        return a.priority < b.priority; 
    }
};

bool cmp_arrival(const Process &a, const Process &b) {
    return a.arrivalTime < b.arrivalTime;
}

int main() {
    vector<Process> p = {
        {1, 0, 5, 2},
        {2, 1, 3, 1},
        {3, 2, 8, 3},
        {4, 4, 6, 2}
    };

    vector<int> burst_time;
    vector<int> waiting_time;
    vector<int> id;

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

            id.push_back(cur.id);

            int waitingTime = currentTime - cur.arrivalTime;
            int turnaroundTime = waitingTime + cur.burstTime;

            burst_time.push_back(cur.burstTime);
            
            totalWaitingTime += waitingTime;
            totalTurnaroundTime += turnaroundTime;
            
            waiting_time.push_back(waitingTime);
            
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

    cout << "Gantt chart: \n";
    int last = currentTime;
    cout << " ";
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < burst_time[i]; j++) 
            cout << "--";
        cout << " ";
    }

    cout << "\n|";
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < burst_time[i] - 1; j++)  cout << " ";
        cout << "p" << id[i];
        for(int j = 0; j < burst_time[i] - 1; j++) cout << " ";
        cout << "|";
    }
    cout << endl;

    cout << " ";
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < burst_time[i]; j++) 
            cout << "--";
        cout << " ";
    }
    cout << endl;

    int minus = 0;
    for(int i = 0; i < n; i++) {
        if (waiting_time[i] > 9) cout << " ";
        cout << waiting_time[i];
        if (i + 1 < n and waiting_time[i + 1] > 9) {
          minus = 1;
        }
        if (i + 1 == n)  
            if (last > 9) minus = 1;
        for(int j = 0; j < burst_time[i] - minus; j++) cout << "  ";
    }
    if (last > 9) printf(" ");
    cout << last;
}