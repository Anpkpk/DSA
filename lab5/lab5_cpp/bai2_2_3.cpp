# include <bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node *next;
    Node(int val) : data(val), next(nullptr) {}
};

class Stack {
private:
    Node *top;

public:
    Stack() : top(nullptr) {}
    ~Stack() {
        while (top != nullptr) {
            Node *tmp = top;
            top = top->next;
            delete tmp;
        }
    }

    void push(int val) {
        Node *new_node = new Node(val);

        new_node->next = top;
        top = new_node;
    }

    int pop() {
        if (top == nullptr) return 0;

        int value = top->data;

        Node *tmp = top;
        top = top->next;
        delete tmp;

        return value;
    }

    int peek() {
        if (top == nullptr) return 0;
        return top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    int size() {
        int s = 0;

        Node *tmp = top;
        while (tmp != nullptr) {
            tmp = tmp->next;
            s++;
        }

        return s;
    }
};


class StackQueue {
private:
    Stack s1, s2;

public:
    StackQueue() {}
    ~StackQueue() {
        s1.~Stack();
        s2.~Stack();
    }

    void enqueue(int val) {
        s1.push(val);
    }

    int dequeue() {
        if (isEmpty()) return 0;

        if (s2.isEmpty()) {
            while (!s1.isEmpty()) {
                s2.push(s1.pop());
            }
        }
        return s2.pop();
    }

    bool isEmpty() {
        return s1.isEmpty() and s2.isEmpty();
    }
};

int main() {
    StackQueue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    cout << q.dequeue() << endl; // 1
    cout << q.dequeue() << endl; // 2
    cout << q.dequeue() << endl; // 3
}