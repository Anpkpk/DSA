#include <bits/stdc++.h>

using namespace std;

class Student {
private: 
    int msv;
    string name;
    int age;
    double gpa;
public:
    Student() {
        this->msv = 0;
        this->name = "Unkown";
        this->age = 0;
        this->gpa = 0.0;
    }
    
    Student(int msv, string name, int age, double gpa) {
        this->msv = msv;
        this->name = name;
        this->age = age;
        this->gpa = gpa;
    }

    int getMsv() {
        return msv; 
    }

    string getName() { 
        return name; 
    }

    int getAge() { 
        return age; 
    }

    double getGpa() { 
        return gpa; 
    }

    void setMsv(int msv) { 
        this->msv = msv; 
    }

    void setName(string& name) { 
        this->name = name; 
    }

    void setAge(int age) {
        if (age > 0) {
            this->age = age; 
        }
    }

    void setGpa(double gpa) { 
        if (gpa > 0.0) {
            this->gpa = gpa; 
        }
    }

    void displayInfo() {
        cout << "MSV: " << msv  << endl
             << "Name: " << name << endl
             << "Age: " << age << endl
             << "GPA: " << gpa << endl;
    }

    bool isHonorStudent() {
        return gpa >= 3.6;
    }
};

int main() {
    int n;
    cin >> n;

    Student *students = new Student[n];

    int msv, age;
    string name;
    double gpa;

    for (int i = 0; i < n; i++) {
        cout << "Student " << i + 1 << ":" << endl;
        
        cout << "\t msv: ";
        cin >> msv;
        cin.ignore();    
        
        cout << "\t name: ";
        getline(cin, name);
        
        cout << "\t age: ";
        cin >> age;
        
        cout << "\t gpa: ";
        cin >> gpa;
        
        students[i] = Student(msv, name, age, gpa);
    }

    for (int i = 0; i < n; i++) {
        students[i].displayInfo();
    }

    delete[] students;
}