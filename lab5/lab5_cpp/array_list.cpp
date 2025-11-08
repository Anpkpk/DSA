#include <bits/stdc++.h>

using namespace std;

class ArrayList {
private:
    int *arr;
    int capacity;
    int length;
public:
    ArrayList(int cap) {
        capacity = cap;
        length = 0;
        arr = new int[capacity];
    }
    ~ArrayList() {
        delete[] arr;
    } 

    int size() {
        return length;
    }

    int get(int index) {
        return arr[index];
    }
    
    void append(int value) {
        if (length == capacity) {
            int newCapacity = capacity + 1;

            int* newArr = new int[newCapacity];
            
            for (int i = 0; i < capacity; ++i)
                newArr[i] = arr[i];
            delete[] arr;

            arr = newArr;
            capacity = newCapacity;
        }
        arr[length++] = value;
    }

    void insert(int index, int value) {
        if (index < 0) {
            index = 0;
        }
        else if (index > length) {
            index = length - 1;
            int newCapacity = capacity + 1;
            
            int* newArr = new int[newCapacity];
            
            for (int i = 0; i < capacity; ++i)
                newArr[i] = arr[i];
            delete[] arr;

            arr = newArr;
            capacity = newCapacity;
        }

        length++;
        for (int i = length - 1; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = value; 
    }

    void remove(int index) {
        for (int i = index; i < length - 1; i++) {
            arr[i] = arr[i + 1];
        }
        length--;
    }

    bool isEmpty() {
        return length == 0 ? true : false;
    }

    void display() {
        for (int i = 0; i < length; i++) {
            if (i < length) {
                cout << arr[i] << " ";
            }
            else {
                cout << arr[i];
            }
        }
        cout << endl;
    }
};

int main() {
    ArrayList arr(4);

    arr.append(1);
    arr.append(2);
    arr.append(3);

    cout << arr.size() << endl;
    arr.display();

    arr.insert(2, 5);
    arr.display();

    arr.remove(2);
    arr.display();
}