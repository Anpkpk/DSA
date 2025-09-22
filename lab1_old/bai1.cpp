#include<iostream>

using namespace std;

string even_odd(int a) {
    if (a % 2 == 0) {
        return "even";
    }
    else return "odd";
}

int main() {
    int a;
    cin >> a;
    
    cout << even_odd(a);
}