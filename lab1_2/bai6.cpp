#include <bits/stdc++.h>

using namespace std;

class DynamicString {
private:
    char* data; 
    int len;

public:
    DynamicString() {
        this->data = nullptr;
        this->len = 0;
    }

    DynamicString(const char* str) {
        this->len = strlen(str);
        this->data = new char[len + 1]; 
        strcpy(data, str);
    }

    DynamicString(const DynamicString& other) {
        this->len = other.len;
        if (len > 0) {
            data = new char[len + 1];
            strcpy(data, other.data);
        } else {
            data=nullptr;
        }
    }

    ~DynamicString() {
        delete[] data;
    }

    DynamicString& operator=(const DynamicString& other) {
        if (this == &other) {
            return *this;
        }

        delete[] data;

        len = other.len;
        if (len > 0) {
            data = new char[len + 1];
            strcpy(data, other.data);
        } else {
            data = nullptr;
        }
        return *this;
    }

    int length() {
        return len;
    }


    void append(const char* str) {
        int addLen = strlen(str);
        char* newData = new char[this->len + addLen + 1];

        if (this->data) {
            strcpy(newData, this->data);
        }
        else {
            newData[0] = '\0';
        }

        strcat(newData, str);

        delete[] data;

        this->data = newData;
        len += addLen;
    }

    DynamicString substring(int pos, int count) {
        if (pos < 0 || pos >= this->len || count <= 0) {
            return DynamicString();
        }

        int realCount;
        if (pos + count > len) {
            realCount = len - pos;
        } 
        else {
            realCount = count;
        }
            
        char* sub = new char[realCount + 1];
        strncpy(sub, this->data + pos, realCount);
        sub[realCount] = '\0';

        DynamicString result(sub);
        
        delete[] sub;
        return result;
    }

    void print() {
        if (data) {
            cout << data;
        }
        else {
            cout << "nullptr";
        }
    }
};


int main() {
    DynamicString s1("Hello");
    s1.print(); 
    cout << endl;

    DynamicString s2 = s1;
    s2.print(); 
    cout << endl;

    DynamicString s3("Temp");
    s3.print(); 
    s3 = s1; 
    s3.print(); 
    cout << endl;

    s1.append(" World!");
    s1.print(); 
    cout << endl;

    DynamicString sub = s1.substring(6, 5);
    sub.print(); 
    cout << endl;

}