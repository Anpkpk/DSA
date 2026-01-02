#include <bits/stdc++.h>
using namespace std;

class Medium {
private:
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

public:
    void addNum(int x) {
        if (maxHeap.empty() or x <= maxHeap.top())
            maxHeap.push(x);
        else
            minHeap.push(x);

        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedium() {
        int total = maxHeap.size() + minHeap.size();
        if (total % 2 != 0) 
            return maxHeap.top();
        else
            return (maxHeap.top() + minHeap.top())/2.0;
    }
};

int main() {
    Medium medium;
    medium.addNum(1);
    medium.addNum(3);
    medium.addNum(2);
    medium.addNum(4);
    medium.addNum(9);

    cout << medium.findMedium() << endl;
}