#include <bits/stdc++.h>

using namespace std;

class Queue {
private:
    int* arr;
    int capacity;
    int front;
    int rear;
    int length;
public:
    Queue(int cap) {
        capacity = cap;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        length = 0;
    }
    
    ~Queue() {
        delete[] arr;
    }

    void enqueue(int value) {
        if (length == capacity) 
            return;
        rear++;
        arr[rear] = value;
        length++;
    }

    int dequeue() {
        if (isEmpty())
            return -1;
        int first = arr[front];
        front++;
        length--;
        return first;
    }

    int peek() {
        if (isEmpty()) return 0;
        return arr[front];
    }

    bool isEmpty() {
        return length == 0;
    }

    int size() {
        return length;
    }
};

int main() {
    Queue q(5);
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    cout << q.dequeue() << endl;  
    cout << q.peek() << endl;   
    cout << q.size() << endl;
}
 