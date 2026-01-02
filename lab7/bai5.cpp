#include <bits/stdc++.h>
using namespace std;

void heapifyDown(vector<int> &arr, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n and arr[l] > arr[largest])
        largest = l;

    if (r < n and arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapifyDown(arr, n, largest);
    }
}

void heapifyUp(vector<int> &arr, int n, int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (arr[p] <= arr[i]) break;
        swap(arr[p], arr[i]);
        i = p;
    }
}

void builMaxheap(vector<int> &arr) {
    for (int i = arr.size()/2 - 1; i >= 0; i--) 
        heapifyDown(arr, arr.size(), i);
}

// vector<int> kElementMax(vector<int> &arr, int k) {
//     builMaxheap(arr);
//     vector<int> ans;
//     int n = arr.size();

//     while (k-- and n > 0) {
//         ans.push_back(arr[0]);
//         swap(arr[0], arr[n - 1]);
//         n--;
//         heapifyDown(arr, n, 0);
//     }

//     return ans;
// } 

void builMinheap(vector<int> &arr) {
    for (int i = arr.size()/2 - 1; i >= 0; i--) 
        heapifyUp(arr, arr.size(), i);
}

vector<int> kElementMax(vector<int> &arr, int k) {
    vector<int> heap;

    for (int x : arr) {
        if (heap.size() < k) {
            heap.push_back(x);
            heapifyUp(heap, heap.size() - 1, 0);
        }
        else if (x > heap[0]) {
            heap[0] = x;
            heapifyDown(heap, k, 0);
        }
    }
    return heap;
} 

int main() {
    vector<int> arr = {4, 10, 3, 5, 1};
    vector<int> ans = kElementMax(arr, 4);

    for (int x : ans) cout << x << " ";
    cout << endl;
}