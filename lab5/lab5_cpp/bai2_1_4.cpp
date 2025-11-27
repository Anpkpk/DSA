#include <bits/stdc++.h>
using namespace std;

int evaluatePostfix(string postfix) {
    stack<int> st;

    for (char c : postfix) {
        if (c >= '0' and c <= '9') {
            st.push(c - '0');
        } else {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();

            int tmp;
            switch (c) {
                case '+': tmp = a + b; break;
                case '-': tmp = a - b; break;
                case '*': tmp = a * b; break;
                case '/': tmp = a / b; break;
                default: continue;
            }
            st.push(tmp);
        }
    }
    return st.top();
}

int prec(char c) {
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

string infixToPostfix(string infix) {
    string postfix;
    stack<char> st;

    for (char c : infix) {
        if (isdigit(c)) {
            postfix += c;
        }
        else if (c == '(') {
            st.push(c);
        }
        else if (c == ')') {
            while (!st.empty() and st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop();
        }
        else {
            while (!st.empty() and prec(st.top()) >= prec(c)) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }

    return postfix;
}

int evaluateInfix(string infix) {
    string postfix = infixToPostfix(infix);
    int ans = evaluatePostfix(postfix);
    return ans;
}

int main() {
    cout << evaluateInfix("3*6");
}
