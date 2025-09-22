#include <bits/stdc++.h>

using namespace std;

class Student {
private: 
    int msv;
    string name;
    int age;
    double gpa;
public:
    Student(){
        this->msv = 0;
        this->name = "Unkown";
        this->age = 0;
        this->gpa = 0.0;
    }
    
    Student(int msv, string name, int age, double gpa){
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
        this->age = age; 
    }

    void setGpa(double gpa) { 
        this->gpa = gpa; 
    }

    void displayInfo() const {
        cout << "MSV: " << msv  << endl
             << "Name: " << name << endl
             << "Age: " << age << endl
             << "GPA: " << gpa << endl;
    }

    bool isHonorStudent() const {
        return gpa >= 3.5;
    }
};

int main() {
    int n;
    cin >> n;

    Student *students = new Student[n];
}