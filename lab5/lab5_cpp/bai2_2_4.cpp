#include <bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node* next; // pointer to the next node
    Node(int val) : data(val), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* cursor; // pointer to a node in the circular list
    int length = 0;
public:
    CircularLinkedList() : cursor(nullptr) {}
    ~CircularLinkedList() {
        if (!cursor) return;

        Node* start = cursor->next;
        Node* current = start;
        do {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != start);
        cursor = nullptr;
    }

    void insertAfter(int value) {
        Node *new_node = new Node(value);
        if (cursor == nullptr) {
            new_node->next = new_node;
            cursor = new_node;
        } else {
            new_node->next = cursor->next;
            cursor->next = new_node;
        }
        length++;
    }

    void removeAfter() {
        if (cursor == nullptr) return; 

        Node* temp = cursor->next;

        if (temp == cursor) {
            delete temp;
            cursor = nullptr;
            length = 0;
            return;
        } 

        cursor->next = temp->next;
        delete temp;
        length--;
    }

    void advance() {
        if (cursor == nullptr) return;

        if (cursor->next != nullptr) {
            cursor = cursor->next;
        }
    }

    int getFront() {
        if (cursor == nullptr) return 0; 
        return cursor->next->data;
    }

    int getBack() {
        if (cursor == nullptr) return 0; 
        return cursor->data;
    }

    bool isEmpty() {
        return (cursor == nullptr) ? true : false;
    }
    
    int size() {
        return length;
    }

};

int josephusQueue(int n, int k) {
    queue<int> q;

    for (int i = 1; i <= n; i++) {
        q.push(i);
    }

    while (q.size() != 1) {
        for (int i = 0; i < k - 1; i++) {
            int x = q.front();
            q.pop();
            q.push(x);
        }
        q.pop();
    }

    return q.front();
}

int josephusCircularLinkedList(int n, int k) {
    CircularLinkedList cl;

    for (int i = 1; i <= n; i++) {
        cl.insertAfter(i);
    }

    while (cl.size() > 1) {
        for (int i = 1; i < k; i++) {
            cl.advance();
        }
        cl.removeAfter();
    }

    return cl.getBack();
}

int main() {

}