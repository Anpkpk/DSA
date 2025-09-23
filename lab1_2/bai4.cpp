#include <bits/stdc++.h>

using namespace std;

class Employee {
protected:
    string name;
    int age;
    double baseSalary;

public:
    Employee(string name, int age, double baseSalary) {
        this->name = name;
        this->age = age;
        this->baseSalary = baseSalary;
    }

    virtual double calculateSalary() {
        return baseSalary;
    }

    virtual void displayInfo() {
        cout << "Name: " << name << endl
             << "Age: " << age << endl
             << "Base Salary: " << baseSalary << endl;
    }

    virtual ~Employee() {}
};


class Manager : public Employee {
private:
    double allowance;

public:
    Manager(string name, int age, double baseSalary, double allowance)
        : Employee(name, age, baseSalary) {
            this->allowance = allowance;
    }

    double calculateSalary() override {
        return baseSalary + allowance;
    }

    void displayInfo() override {
        cout << "Manager " << endl;
        Employee::displayInfo();
        cout << "Allowance: " << allowance << endl
             << "Total Salary: " << calculateSalary() << endl;
    }
};

class Developer : public Employee {
private:
    string pro_lang;

public:
    Developer(string name, int age, double baseSalary, string pro_lang)
        : Employee(name, age, baseSalary) {
            this->pro_lang = pro_lang;
    }

    double calculateSalary() override {
        if (pro_lang == "Python")
            return baseSalary + 1000;
        return baseSalary + 500;
    }

    void displayInfo() override {
        cout << "Developer " << endl;
        Employee::displayInfo();
        cout << "Language: " << pro_lang << endl
             << "Total Salary: " << calculateSalary() << endl;
    }
};

int main() {
    vector<Employee> employees;

    employees.push_back(Manager("An", 40, 3000, 1500));
    employees.push_back(Developer("Hai", 25, 2000, "C++"));
    employees.push_back(Developer("Dung", 28, 2200, "Python"));

    cout << "Employee List:" << endl;
    for (auto emp : employees) {
        emp.displayInfo();
    }
}
