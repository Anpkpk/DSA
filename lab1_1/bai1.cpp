#include <iostream>

using namespace std;

int *create_array(int n) {
    int *a = new int[n];
    return a;
}

void delete_array(int *a) {
    delete[] a;
}

void scan_array(int *a, int n) {
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
}

void print_array(int *a, int n) {
    for (int i = 0; i < n; i++) {
        if (i < n - 1) {
            cout << a[i] << " ";
        }
        else cout << a[i];
    }

}

void sum_of_element(int *a, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    cout << "Sum = " << sum << endl;
}

void min_max(int *a, int n) {
    int max = a[0];
    int min = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
        if (a[i] < min) {
            min = a[i];
        }
    }
    cout << "Max = " << max << ", Min = " << min << endl;
}

void my_sort(int *a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                swap(a[i], a[j]);
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    int *a = create_array(n);
    scan_array(a, n);

    sum_of_element(a, n);

    min_max(a, n);

    my_sort(a, n);
    print_array(a, n);

    delete_array(a);
}
