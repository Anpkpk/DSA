#include <bits/stdc++.h>

using namespace std;

void heapifyDown(int arr[], int n, int i) {
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


void heapSort(int a[], int n) {
    for (int i = n/2 - 1; i >= 0; i--) 
        heapifyDown(a, n, i);
    
    for (int i = n - 1; i > 0; i--){
        swap(a[i], a[0]);
        heapifyDown(a, i, 0);
    }
}

int main() {
    int arr[] = {4, 10, 3, 5, 1};
    int n = 5;

    heapSort(arr, n);
    for (int x : arr) 
        cout << x << " ";
    cout << endl;
}