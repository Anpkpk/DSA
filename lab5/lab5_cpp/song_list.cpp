#include <bits/stdc++.h>

using namespace std;

struct Node {
    string title;
    Node* next;
    Node(string val) : title(val), next(nullptr) {}
};

class SongList {
private:
    Node *cursor;
public:
    SongList() : cursor(nullptr) {}
    
    ~SongList() {
        if (!cursor) return;

        Node* start = cursor->next;
        Node* current = start;
        if (cursor == cursor->next) {
            delete cursor;
        } else {
            do {
                Node* nextNode = current->next;
                delete current;
                current = nextNode;
            } while (current != start);
        }
        cursor = nullptr;
    }

    
    void addSong(string title){
        Node *new_node = new Node(title);
        if (cursor == nullptr) {
            new_node->next = new_node;
            cursor = new_node;
        } else {
            new_node->next = cursor->next;
            cursor->next = new_node;
            cursor = new_node;
        }
    }

    void removeCurrentSong() {
        if (!cursor) return;

        if (cursor->next == cursor) { 
            delete cursor;
            cursor = nullptr;
            return;
        }

        Node* prev = cursor;
        while (prev->next != cursor) 
            prev = prev->next;

        prev->next = cursor->next;
        delete cursor;
        cursor = prev;
    }

    void nextSong() {
        if (cursor == nullptr) return;

        if (cursor->next != nullptr) {
            cursor = cursor->next;
        }
    }

    string currentSong() {
        if (cursor == nullptr) return "none";
        return cursor->title;
    }

    void displayPlaylist() {
        if (cursor == nullptr) {
            cout << "List is empty" << endl;
            return;
        }

        Node* start = cursor->next;
        Node* tmp = start;
        do {
            cout << tmp->title << " -> ";
            tmp = tmp->next;
        } while (tmp != start);
        cout << "(back to front)" << endl;
    }

};

int main() {
    SongList a;
    a.addSong("1");
    a.addSong("2");
    a.addSong("3");
    a.addSong("4");


    a.displayPlaylist();
    cout << a.currentSong() << endl;

    a.removeCurrentSong();
    a.displayPlaylist();
    cout << a.currentSong() << endl;
}