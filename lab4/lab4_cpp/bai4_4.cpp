#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

template<typename Func>
double measureTime(Func func) {
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    return duration.count() / 1000.0;
}

void insertion_sort(int *a, int n) {
    for (int i = 1; i < n; ++i) {
        int key = a[i];
        
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        
        a[j + 1] = key;
    }
}

int median_of_three(int *a, int left, int right) {
    int mid = (left + right) / 2;
    if (a[left] > a[mid]) swap(a[left], a[mid]);
    if (a[left] > a[right]) swap(a[left], a[right]);
    if (a[mid] > a[right]) swap(a[mid], a[right]);
    
    return a[mid];
}


int hoare_partition(int *a, int l, int r) {
    int x = median_of_three(a, l, r);

    int i = l - 1;
    int j = r + 1;
    
    while (1) {
        do {
            j--;
        } while (a[j] > x);
        
        do {
            i++;
        } while (a[i] < x);
        
        if (i < j) {
            swap(a[i], a[j]);
        } else return j;
    }
}


void quick_sort(int *a, int l, int r) {
    if (l < r) {
        int q = hoare_partition(a, l, r);
        quick_sort(a, l, q );   
        quick_sort(a, q + 1, r);
    }
}

void chybird_sort(int *a, int l, int r) {
    if (r - l < 10) {
        insertion_sort(a + l, r - l);
    } else {
        quick_sort(a, l, r);
    }
}

int main() {
     srand(0);
    const int N = 1'000'000; // 10^6 phần tử
    vector<int> original(N);
    for (int i = 0; i < N; i++) original[i] = rand();

    vector<int> arr1 = original;
    vector<int> arr2 = original;

    cout << "Benchmark sorting with " << N << " elements...\n";

    double t1 = measureTime([&]() {
        quick_sort(arr1.data(), 0, N - 1);
    });

    double t2 = measureTime([&]() {
        chybird_sort(arr2.data(), 0, N - 1);
    });

    cout << fixed << setprecision(3);
    cout << "Quick Sort:    " << t1 << " ms\n";
    cout << "CHybrid Sort: " << t2 << " ms\n";
    cout << "Quick Sort/CHybrid Sort: " << (t1 / t2) << "x\n";
}