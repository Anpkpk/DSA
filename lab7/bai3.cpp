#include <bits/stdc++.h>
using namespace std;

struct Item {
    int priority;
    int value;
    long long timestamp;
    Item(int pri, int val, long long times) : priority(pri), value(val), timestamp(times) {}
};

class PriorityQueue {
private:
    vector<Item> heap;
    long long timer = 0;

    int parent(int i) {
        return (i - 1)/2;
    }

    int left(int i) {
        return 2*i + 1;
    }

    int right(int i) {
        return 2*i + 2;
    }

    void swap(Item &a, Item &b) {
        Item tmp = a;
        a = b;
        b = tmp;
    }

    bool higherPriority(const Item &a, const Item &b) {
        if (a.priority != b.priority)
            return a.priority < b.priority;   
        return a.timestamp < b.timestamp;  
    }

    void heapifyUp(int i) {
        while (i > 0) {
            int p = parent(i);
            if (!higherPriority(heap[i], heap[p]))
                break;
            swap(heap[p], heap[i]);
            i = p;
        }
    }

    void heapifyDown(int i) {
        int smallest = i;
        int l = left(i);
        int r = right(i);
        
        if (l < heap.size() and higherPriority(heap[l], heap[smallest]))
            smallest = l;
            
        if (r < heap.size() and higherPriority(heap[r], heap[smallest]))
            smallest = r;
    
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }


public:
    bool isEmpty() {
        return heap.size() == 0;
    }

    void push(int priority, int val) {
        Item x(priority, val, timer++);

        heap.push_back(x);
        heapifyUp(heap.size() - 1);
    }

    Item top() {
        return heap[0];
    }

    void pop() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

};

int main() {
    PriorityQueue pq;

    pq.push(3, 100);
    pq.push(10, 200);
    pq.push(1, 300);
    pq.push(5, 400);
    pq.push(5, 500);
    pq.push(5, 600);


    while (!pq.isEmpty()) {
        Item x = pq.top();
        cout << "priority=" << x.priority
             << " value=" << x.value << endl;
        pq.pop();
    }
}