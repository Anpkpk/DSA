#include <bits/stdc++.h>
using namespace std;

class MinHeap {
private:
    vector<int> arr;
    int parent(int i) { 
        return (i - 1) / 2; 
    }
    
    int left(int i) { 
        return 2 * i + 1; 
    }

    int right(int i) { 
        return 2 * i + 2; 
    }

    void minHeapify(int i, int heapSize) {
        int smallest = i;
        int l = left(i);
        int r = right(i);

        if (l < heapSize and arr[l] < arr[smallest])
            smallest = l;

        if (r < heapSize and arr[r] < arr[smallest])
            smallest = r;

        if (smallest != i) {
            swap(arr[i], arr[smallest]);
            minHeapify(smallest, heapSize);
        }
    }

    void heapDecreaseKey(int i, int newKey) {
        if (newKey > arr[i]) {
            cout << "new key is greater than current key";
            return;
        }

        arr[i] = newKey;

        while (i > 0 and arr[parent(i)] > arr[i]) {
            swap(arr[i], arr[parent(i)]);
            i = parent(i);
        }
    }


public:
    bool empty() const { 
        return arr.empty(); 
    }

    int size() const { 
        return (int)arr.size(); 
    }

    int minimum() const {
        return arr[0];
    }

    void insert(int key) {
        arr.push_back(INT_MAX);
        heapDecreaseKey(arr.size() - 1, key);
    }

    int extractMin() {
        int minVal = arr[0];
        arr[0] = arr.back();
        arr.pop_back();

        if (!arr.empty()) 
            minHeapify(0, arr.size());

        return minVal;
    }

    void buildMinHeap(const vector<int> &arr) {
        this->arr = arr;
        for (int i = arr.size()/2 - 1; i >= 0; i--) {
            minHeapify(i, arr.size());
        }
    }

    void printArray() const {
        for (int x : arr)
            cout << x << " ";
        cout << endl;
    }
    
    void heapSort(vector<int>& a) {
        arr = a;
        buildMinHeap(arr);

        for (int i = arr.size() - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            minHeapify(0, i);
        }
        a = arr;
    }
};

int main() {
    vector<int> arr = {1, 3, 2, 7, 6, 4, 0};
    MinHeap mh;
    mh.heapSort(arr);
    
    for (int x : arr) 
        cout << x << " ";
    cout << endl;
}