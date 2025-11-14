#include <bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node *next;
    Node(int val) : data(val), next(nullptr) {}
};

class Queue {
private: 
    Node *front;
    Node *rear;
    int length;

public:
    Queue() : front(nullptr), rear(nullptr), length(0) {}
    
    ~Queue() {
    }

    void enqueue(int value) {
        Node *new_node = new Node(value);

        if (isEmpty())
            front = rear = new_node;
        else {
            rear->next = new_node;
            rear = new_node;
        }
        length++;
    }

    int dequeue() {
        if (isEmpty()) return 0;
        
        int val = front->data;
        
        Node *tmp = front;
        front = front->next;

        length--;
        if (length==0) rear = nullptr;

        delete tmp;

        return val;
    }

    int front() {
        if (isEmpty()) return 0;
        return front->data;
    }

    bool isEmpty() {
        return length == 0;
    }

    int size() {
        return length;
    }
};