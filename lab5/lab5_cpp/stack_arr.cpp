#include <bits/stdc++.h>

using namespace std;

class Stack {
private:
    int *arr;
    int capacity;
    int top;
public:
    Stack(int cap) {
        capacity = cap;
        arr = new int[capacity];
        top = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    void push(int value) {
        arr[++top] = value; 
    }

    int pop() {
        return arr[top--];
    }

    int peek() {
        return arr[top]; 
    }

    bool isEmpty() {
        return (top == -1) ? true : false;
    }

    int size() {
        return top;
    }
};

int main() {
    Stack s(5);
    s.push(1);
    s.push(2);
    s.push(3);

    while (!s.isEmpty()) {
        cout << s.pop() << " ";
    }

    
}