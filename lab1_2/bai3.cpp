#include <bits/stdc++.h>

using namespace std;

class BankAccount {
private:
    int account_number;
    string owner_name;
    double balance;

public:
    BankAccount() {}

    BankAccount(int account_number, string owner_name, double balance=0.0) {
        this->account_number = account_number;
        this->owner_name = owner_name;
        this->balance = balance;
    }

    int getAccountNumber() { 
        return account_number; 
    }
    
    string getOwnerName() { 
        return owner_name; 
    }

    double getBalance() { 
        return balance; 
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Nap " << amount << " thanh cong.\n";
        } 
        else {
            cout << "Amount > 0!\n";
        }
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Amount > 0!\n";
        } 
        else if (amount > balance) {
            cout << "Het tien.\n";
        } 
        else {
            balance -= amount;
            cout << "Rut " << amount << " thanh cong.\n";
        }
    }

    void transfer(BankAccount &toAccount, double amount) {
        if (amount <= 0) {
            cout << "Amount > 0!\n";
        } 
        else if (amount > balance) {
            cout << "Het tien.\n";
        } 
        else {
            this->balance -= amount;
            toAccount.balance += amount;
            cout << "Chuyen " << amount << " thanh cong.\n";
        }
    }

    void displayInfo() {
        cout << "Account: " << account_number << endl
             << "Owner: " << owner_name << endl
             << "Balance: " << balance << endl;
    }
};

int main() {
    vector<BankAccount> accounts;

    accounts.push_back(BankAccount(1001, "Nguyen Huy Hoang An", 1000));
    accounts.push_back(BankAccount(1002, "Nguyen Tien Dung", 2000));
    accounts.push_back(BankAccount(1003, "Ta Thanh Hai", 50000));

    for (auto acc : accounts) {
        acc.displayInfo();
    }

    accounts[0].deposit(2000);

    accounts[1].withdraw(500);

    accounts[2].transfer(accounts[1], 10000);

    for (auto acc : accounts) {
        acc.displayInfo();
    }
}