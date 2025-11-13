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
    }

    void removeAfter() {
        if (cursor == nullptr) return; 

        Node* temp = cursor->next;

        if (temp == cursor) return;

        cursor->next = temp->next;
        delete temp;
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
        return (cursor != nullptr) ? true : false;
    }
        
    void display() {
        if (cursor == nullptr) {
        cout << "List is empty" << endl;
        return;
        }

        Node* start = cursor->next;
        Node* tmp = start;
        do {
            cout << tmp->data << " -> ";
            tmp = tmp->next;
        } while (tmp != start);
        cout << "(back to front)" << endl;
    }
};

int main() {

}
