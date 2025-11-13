#include <bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node * next; // pointer to the next node
    Node * prev; // pointer to the previous node
    Node (int val) : data (val), next (nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private :
    Node *head;
    Node *tail;
public :
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    
    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
    }

    void insertHead (int value) {
        Node *new_node = new Node(value);

        if (head != nullptr) {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        else {
            head = tail = new_node;
        }
    }

    void insertTail (int value ) {
        Node *new_node = new Node(value);

        if (head == nullptr) {  
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node; 
        }
    }

    void removeHead() {
        if (head == nullptr)
            return;

        Node* tmp = head;

        if (head->next == nullptr) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete tmp;
    }


    void removeTail() {
        if (head == nullptr)
            return;

        Node *tmp = tail;

        if (head->next == nullptr) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete tmp;
    }

    Node * search(int value) {
        Node *tmp = head;
        if (head == nullptr) 
            return nullptr;
        
        while (tmp) {
            if (tmp->data == value) 
                return tmp;
            else
                tmp = tmp->next;
        }
        return nullptr;
    }

    void displayForward() {
        Node *tmp = head;
        while (tmp != nullptr) {
            cout << tmp->data << " <-> ";
            tmp = tmp->next;
        }
        cout << "nullptr" << endl;
    }

    void displayBackward() {
        Node *tmp = tail;
        while (tmp != nullptr) {
            cout << tmp->data << " <-> ";
            tmp = tmp->prev;
        }
        cout << "nullptr" << endl;
    }
};
int main() {
    DoublyLinkedList lk = DoublyLinkedList();
    lk.insertHead(1);
    lk.insertHead(2);
    lk.insertHead(3);
    lk.insertHead(6);
    lk.insertHead(4);

    lk.displayBackward();
    lk.displayForward();
}