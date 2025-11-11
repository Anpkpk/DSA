#include <bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node *next; // pointer to the next node
    Node *prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    Node *head; // pointer to the head of the list
public:
    DoublyLinkedList() : head(nullptr) {}
    ~DoublyLinkedList() {}
    
    void insertHead(int value) {
        Node *new_node = new Node(value);
        new_node->next = head;
        new_node->prev = nullptr;
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
        new_node->prev = tmp;
    }

    void removeHead() {
        if (head == nullptr)
            return;

        Node *tmp = head;
        head = head->next;

        if (head != nullptr)
            head->prev = nullptr;
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
        while (tmp->next != nullptr) {
            tmp = tmp->next;
        }
        
        tmp->prev->next = nullptr;
        delete tmp;
    }

    Node *search(int value) {
        Node *tmp = head;
        while (tmp != nullptr and tmp->data != value) {
            tmp = tmp->next;
        }
        return tmp;
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
        Node *it = head;

        while (it != nullptr) {
            Node *it1 = it->next;
            while (it1 != nullptr) {
                Node *next_node = it1->next;

                if (it1->data == it->data) {
                    if (it1->prev != nullptr)
                        it1->prev->next = it1->next;

                    if (it1->next != nullptr)
                        it1->next->prev = it1->prev;

                    delete it1;
                }

                it1 = next_node;
            }
            it = it->next;
        }
    }


    Node *getHead() {
        return head;
    }

    void deleteList(DoublyLinkedList &lk) {
        while (lk.getHead() != nullptr) {
            lk.removeHead();
        }
    }

    void insert(int index, int value) {
        Node *tmp = head;
        Node *new_node = new Node(value);

        if (head == nullptr or index == 0) {
            new_node->next = head;
            if (head != nullptr)
                head->prev = new_node;
            head = new_node;
            return;
        }

        int i = 0;
        while (tmp->next != nullptr and i < index - 1) {
            tmp = tmp->next;
            i++;
        }

        if (tmp->next != nullptr)
            tmp->next->prev = new_node;

        new_node->next = tmp->next;
        new_node->prev = tmp;
        tmp->next = new_node;
    }

    void remove(int index) {
        if (head == nullptr) return;

        Node *tmp = head;
        int i = 0;
        while (tmp->next != nullptr and i < index) {
            tmp = tmp->next;
            i++;
        }

        if (tmp == nullptr) return;
        if (tmp->prev == nullptr) {
            removeHead();
            return;
        }

        if (tmp->next != nullptr)
            tmp->next->prev = tmp->prev;
        tmp->prev->next = tmp->next;

        delete tmp;
    }

    int getDataByIndex(DoublyLinkedList lk, int index) {
        Node *tmp = lk.getHead();
        int i = 0;
        while (tmp->next != nullptr and i < index) {
            tmp = tmp->next;
            i++;
        }
        return tmp->data;
    }

    void merge(DoublyLinkedList &other) {
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
        Node *curr = head;
        Node *tmp = nullptr;

        while (curr != nullptr) {
            tmp = curr->prev;
            curr->prev = curr->next;
            curr->next = tmp;

            curr = curr->prev;
        }

        if (tmp != nullptr)
            head = tmp->prev;
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
       if (x == y) return;

        Node *prev_x = nullptr;
        Node *node_x = head;
        while (node_x != nullptr) {
            if (node_x->data != x) {
                prev_x = node_x;
            }
            node_x = node_x->next;
        }

        Node *prev_y = nullptr;
        Node *node_y = head;
        while (node_y != nullptr) {
            if (node_y->data != x) {
                prev_y = node_x;
            }
            node_x = node_x->next;
        }

        if (node_x == nullptr or node_y == nullptr)
            return;

        if (prev_x != nullptr)
            prev_x->next = node_y;
        else
            head = node_y;

        if (prev_y != nullptr)
            prev_y->next = node_x;
        else
            head = node_x;

        Node *temp = node_x->next;
        node_x->next = node_y->next;
        node_y->next = temp;
    }
    
    void removeNthFromEnd(int n) {
        Node *slow = head;
        Node *fast = head;

        if (slow->next == nullptr) 
            return;

        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }

        if(fast == nullptr) return;

        while (fast->next != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }

        slow->next = slow->next->next;
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
    DoublyLinkedList lk = DoublyLinkedList();
    lk.insertHead(1);
    lk.insertHead(2);
    lk.insertHead(1);
    lk.insertHead(3);
    lk.insertHead(1);

    lk.display();
   
    lk.removeDuplicates();
    lk.display();
}