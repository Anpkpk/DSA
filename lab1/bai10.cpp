#include <bits/stdc++.h>

using namespace std;

void menu() {
    cout << "\n===== MENU =====\n";
    cout << "1. Tinh tong\n";
    cout << "2. Tinh hieu\n";
    cout << "3. In chuoi\n";
    cout << "0. Thoat\n";
    cout << "Nhap lua chon: ";
}

int readInt(const string &prompt) {
    string line;
    long long val;
    while (true) {
        cout << prompt;
        if (!getline(cin, line)) {             
            cout << "\nNhap bi ngat. Thoat chuong trinh.\n";
            exit(0);
        }
        stringstream ss(line);
        if (ss >> val) {
            char extra;
            if (!(ss >> extra)) {              
                if (val < INT_MIN || val > INT_MAX) {
                    cout << "Gia tri vuot qua pham vi int. Nhap lai.\n";
                    continue;
                }
                return static_cast<int>(val);
            }
        }
        cout << "Nhap khong hop le. Vui long nhap mot so nguyen.\n";
    }
}

void tinhTong() {
    int a = readInt("Nhap a: ");
    int b = readInt("Nhap b: ");

    cout << "Tong = " << static_cast<long long>(a) + b << endl;
}

void tinhHieu() {
    int a = readInt("Nhap a: ");
    int b = readInt("Nhap b: ");
    cout << "Hieu = " << a - b << endl;
}


void inChuoi() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    string s;
    cout << "Nhap chuoi: ";
    getline(cin, s);
    cout << "Ban vua nhap: " << s << endl;
}

int main() {
    int choice;

    while (true) {

        menu();

        cin >> choice;
        cin.ignore();
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Lua chon khong hop le! Vui long nhap so nguyen.\n";
            continue;
        }

        switch (choice) {
            case 1:
                tinhTong();
                break;
            case 2:
                tinhHieu();
                break;
            case 3:
                inChuoi();
                break;
            case 0:
                cout << "Thoat chuong trinh...\n";
                return 0;
            default:
                cout << "Lua chon khong ton tai, vui long thu lai.\n";
        }
    }

    return 0;
}
