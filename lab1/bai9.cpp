#include <bits/stdc++.h>

using namespace std;

struct student {
    int id;
    int age;
    double gpa;
    string name;
};

void scan_students(student *st, int n) {
    for (int i = 0; i < n; i++) {
        cin >> st[i].id;
        cin.ignore();
        getline(cin, st[i].name);
        cin >> st[i].age;
        cin >> st[i].gpa;
    }
}

void print_students(student *st, int n) {
    for (int i = 0; i < n; i++) {
        cout << st[i].id <<  ' ';
        cout << st[i].name << ' ';
        cout << st[i].age << ' ';
        cout << st[i].gpa << endl;
    }
}

void search_for_id(student *st, int n, int id) {
    for (int i = 0; i < n; i++) {
        if (st[i].id == id) {
            cout << st[i].id <<  ' ';
            cout << st[i].name << ' ';
            cout << st[i].age << ' ';
            cout << st[i].gpa << endl;
            return;
        }
    }
    cout << "invalid id";
}

void sort_for_gpa(student *st, int n) {
    for (int i = 1; i < n; i++) {
        student key = st[i];
        int j = i - 1;

        while (j >= 0 and st[j].gpa > key.gpa) {
            st[j + 1] = st[j];
            j--;
        }
        st[j + 1] = key;
    }
}

int main() {
    int n;
    cin >> n;
    struct student *st = new student[n];
    
    scan_students(st, n);
    print_students(st, n);
    
    // search_for_id(st, n, 1);
    sort_for_gpa(st, n);
    print_students(st, n);

    delete[] st;
}