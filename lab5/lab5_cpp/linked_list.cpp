#include <bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node *next; // pointer to the next node
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node *head; // pointer to the head of the list
public:
    LinkedList() : head(nullptr) {}
    ~LinkedList() {}
    
    void insertHead(int value) {
        Node *new_node = new Node(value);
        new_node->next = head;
        head = new_node;
    }

    void insertTail(int value) {
        Node *new_node = new Node(value);
        if (head == nullptr) { 
            head = new_node; 
            return; 
        }

        Node *tmp = head;
        while (tmp->next != nullptr)
            tmp = tmp->next;
        tmp->next = new_node;
    }

    void removeHead() {
        if (head == nullptr)
            return;

        Node *tmp = head;
        head = head->next;
        delete tmp;
    }

    void removeTail() {
        if (head == nullptr) return;

        if (head->next == nullptr) { 
            delete head;
            head = nullptr;
            return;
        }

        Node *tmp = head;
        while (tmp->next->next != nullptr) {
            tmp = tmp->next;
        }
        
        delete tmp->next;
        tmp->next = nullptr;
    }

    Node *search(int value) {
        Node *tmp = head;
        while (tmp != nullptr) {
            if (tmp->data == value)
                return tmp;
            tmp = tmp->next;
        }
        return nullptr;
    }

    int count(int value) {
        Node *tmp = head;
        int cnt = 0;
        while (tmp != nullptr) {
            if (tmp->data == value)
                cnt++;
            tmp = tmp->next;
        }
        return cnt;
    }

    void removeDuplicates() {
        Node* tmp = head;
        while (tmp != nullptr) {
            Node* prev = tmp;
            Node* curr = tmp->next;

            while (curr != nullptr) {
                if (curr->data == tmp->data) {
                    prev->next = curr->next;
                    delete curr;
                    curr = prev->next;
                } else {
                    prev = curr;
                    curr = curr->next;
                }
            }
            tmp = tmp->next;
        }
    }

    Node *getHead() {
        return head;
    }

    void deleteList(LinkedList &lk) {
        while (lk.getHead() != nullptr) {
            lk.removeHead();
        }
    }

    void insert(int index, int value) {
        Node *tmp = head;
        int i = 0;
        while (tmp->next != nullptr and i < index - 1) {
            tmp = tmp->next;
            i++;
        }
        Node *new_node = new Node(value);
        new_node->next = tmp->next;
        tmp->next = new_node;
    }

    void remove(int index) {
        Node *tmp = head;
        int i = 0;
        while (tmp->next != nullptr and i < index - 1) {
            tmp = tmp->next;
            i++;
        }

        Node* node_del = tmp->next;
        tmp->next = node_del->next;
        delete node_del;
    }

    int getDataByIndex(LinkedList lk, int index) {
        Node *tmp = lk.getHead();
        int i = 0;
        while (tmp->next != nullptr and i < index) {
            tmp = tmp->next;
            i++;
        }
        return tmp->data;
    }

    void merge(LinkedList &other) {
        Node *tmp = other.getHead();
        while (tmp != nullptr) {
            insertTail(tmp->data);
            tmp = tmp->next;
        }
        deleteList(other);
    }

    int size() {
        Node *tmp = head;
        int i = 0;
        while (tmp != nullptr) {
            tmp = tmp->next;
            i++;
        }
        return i;
    }

    void reverse() {
        Node *prev = nullptr;
        Node *curr = head;
        Node *next_node = nullptr;

        while (curr != nullptr) {
            next_node = curr->next; 
            curr->next = prev;      
            prev = curr;            
            curr = next_node;      
        }

        head = prev;                
    }

    Node *reverse(Node *h) {
        Node *prev = nullptr;
        Node *curr = h;
        Node *next_node = nullptr;

        while (curr != nullptr) {
            next_node = curr->next; 
            curr->next = prev;      
            prev = curr;            
            curr = next_node;      
        }

        h = prev;     
        return h;           
    }

    Node *findMiddle() {
        if (head == nullptr) return nullptr;

        Node *slow = head;
        Node *fast = head;

        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    bool isPalindrome() {
        if (head == nullptr || head->next == nullptr)
            return true;

        Node *mid = findMiddle();

        Node *second_half = reverse(mid->next);

        Node *first_half = head;
        Node *temp_second = second_half;
        bool palindrome = true;

        while (temp_second != nullptr) {
            if (first_half->data != temp_second->data) {
                palindrome = false;
                break;
            }
            first_half = first_half->next;
            temp_second = temp_second->next;
        }

        reverse(second_half);

        return palindrome;
    }

    void swapNodes(int x, int y) {

    }

    void display() {
        Node *tmp = head;
        while (tmp != nullptr) {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }

};

int main() {
    LinkedList lk = LinkedList();

    lk.insertTail(3);
    lk.insertTail(6);
    lk.insertTail(3);
    lk.insertTail(6);
    lk.insertTail(3);

    lk.display();

    if (lk.isPalindrome())
        cout << "True";
    else 
        cout << "False";
}