#include <bits/stdc++.h>

using namespace std;

class Counter {
private:
    static int count;
    int id;

public:
    Counter() {
        count++;
        this->id = 1000 + count;
    }

    ~Counter() {
        count--;
    }

    int getId() const {
        return id;
    }

    static int getObjectCount() {
        return count;
    }

    friend bool compareCounters(const Counter& a, const Counter& b);

    friend class CounterManager;
};

bool compareCounters(const Counter& c1, const Counter& c2) {
    return c1.id == c2.id;
}

class CounterManager {
public:
    void printInfo(const Counter& c) {
        cout << "ID: " << c.id << endl;
    }

    void printTotalObjects() {
        cout << "Total objects: " << Counter::getObjectCount() << endl;
    }
};

int Counter::count = 0;

int main() {
    Counter c1, c2, c3;

    CounterManager manager;

    manager.printInfo(c1);
    manager.printInfo(c2);
    manager.printInfo(c3);

    manager.printTotalObjects();

    if (compareCounters(c1, c2)) {
        cout << "c1 == c2" << endl;
    } else {
        cout << "c1 != c2" << endl;
    }
}