#include <bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Stack {
private:
    Node *top;
public:
    Stack() : top(nullptr) {}
    ~Stack() {
        while (top) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }


    void push(int value) {
        Node* new_node = new Node(value);
        new_node->next = top; 
        top = new_node;
    }


    int pop() {
        if (!top) return 0; 

        int value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return value;
    }

    int peek() {
        if (top == nullptr)
            return 0;
        return top->data;
    }


    bool isEmpty() {
        if (top == nullptr)
            return true;
        return false;
    }

    int size() {
        if (isEmpty()) return 0;

        int cnt = 0;
        Node *tmp = top;
        while (tmp != nullptr) {
            cnt++;
            tmp = tmp->next;
        }
    }
};

int main() {
    Stack s;

    cout << "Stack empty? " << (s.isEmpty() ? "Yes" : "No") << endl;

    s.push(10);
    s.push(20);
    s.push(30);

    cout << "Top element: " << s.peek() << endl;
    cout << "Stack size: " << s.size() << endl;

    cout << "Pop: " << s.pop() << endl;

    cout << "Stack empty? " << (s.isEmpty() ? "Yes" : "No") << endl;

    cout << "Pop: " << s.pop() << endl;
    
    cout << "Pop from empty stack: " << s.pop() << endl;

    return 0;
}