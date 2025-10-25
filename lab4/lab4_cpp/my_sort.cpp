#include <bits/stdc++.h>

using namespace std;

void bubble_sort(int *a, int n) {
    bool swapped;
  
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

void selection_sort(int *a, int n) {
    for (int i = 0; i < n - 1; ++i) {

        int min_idx = i;

        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[min_idx]) {
                min_idx = j; 
            }
        }

        swap(a[i], a[min_idx]);
    }
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

void merge(int *L, int l_size, int *R, int r_size, int *a) {
    int i = 0, l = 0, r = 0;

    while (l < l_size && r < r_size) {
        if (L[l] <  R[r]){
            a[i] = L[l];
            i++;
            l++;
        }
        else {
            a[i] = R[r];
            r++;
            i++;
        }
    } 

    while (l < l_size) {
        a[i] = L[l];
        i++;
        l++;
    }

    while (r < r_size) {
        a[i] = R[r];
        i++;
        r++;
    }
}

void merge_sort(int *a, int n) {
    if (n <= 1) return;

    int middle = n/2;
    int i = 0, j = 0;
    int L[middle], R[n - middle];

    for (i = 0; i < n; i++) {
        if (i < middle){
            L[i] = a[i];
        }
        else {
            R[j] = a[i];
            j++;
        }
    }

    merge_sort(L, middle);
    merge_sort(R, n - middle);
    merge(L, middle, R, n - middle, a);
}

void bottom_up_merge_sort(int *a, int n) {
    int *temp = new int[n];
    
    for (int sz = 1; sz < n; sz *= 2) {
        for (int left = 0; left + sz < n; left += 2 * sz) {
            int mid = left + sz - 1;
            int right = std::min(left + 2*sz - 1, n - 1);
            
            // merge into temp
            int i = left, j = mid + 1, k = left;
            while (i <= mid && j <= right) {
                temp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
            }
            while (i <= mid) temp[k++] = a[i++];
            while (j <= right) temp[k++] = a[j++];
            
            // copy back
            for (int p = left; p <= right; ++p)
                a[p] = temp[p];
        }
    }
    delete temp;
}


int hoare_partition(int *a, int l, int r) {
    int x = a[(l + r)/2];
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

int lomuto_partition(int *a, int l, int r) {
    int pivot = a[r];
    int i = l - 1;
    for (int j = l; j < r; j++) {
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[r]);
    return i + 1;
}

void quick_sort(int *a, int l, int r) {
    if (l < r) {
        // int q = hoare_partition(a, l, r);
        // quick_sort(a, l, q );   // for hoare partition
        int q = lomuto_partition(a, l, r);
        quick_sort(a, l, q - 1);
        quick_sort(a, q + 1, r);
    }
}

int binary_search(int *a, int key, int l, int r) {
    while (l <= r) {
        int mid = l + (r - l) / 2;
        
        if (a[mid] == key) {
            return mid;
        } else if (a[mid] < key) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    
    return l;
}

void binary_insertion_sort(int *a, int n) {
    for (int i = 1; i < n; ++i) {
        int key = a[i]; 
        
        int pos = binary_search(a, key, 0, i - 1);

        int j = i - 1;
        while (j >= pos) {
            a[j + 1] = a[j];
            j--;
        }
        
        a[pos] = key;
    }
}

int main() {
    int a[7] = {1, 4, 2, 3, 0, 1, 9};

    bottom_up_merge_sort(a, 6);

    for (auto x : a) {
        cout << x << " ";
    }
    cout << endl;
}