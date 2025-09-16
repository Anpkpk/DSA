#include<iostream>
#include<cmath>

using namespace std;

bool prime(int a) {
    if (a <= 1) return 0;
    if (a < 4) {
        if (a == 2) {
            return 0;
        } 
    }
    for (int i = 2; i <= sqrt(a); i++) {
        if ((a % i) == 0) {
            return 0;
        } 
    }
    return 1;
}

int main() {
    int a;
    cin >> a;

    cout << prime(a);
}