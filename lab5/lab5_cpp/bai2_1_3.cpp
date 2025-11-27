# include <bits/stdc++.h>

using namespace std;

bool isBalanced(string str) {
    stack<char> st;

    if (str[0] == ']' or str[0] == ')' or str[0] == '}') 
        return false;

    for (auto c : str) {
        if (c == '{' or c == '[' or c == '(') {
            st.push(c);
        }
        else if (c == '}' or c == ']' or c == ')') {
            if (st.empty()) return false;

            char top = st.top();
            st.pop();

            if ((c == ')' && top != '(') or
                (c == ']' && top != '[') or
                (c == '}' && top != '{')) {
                return false;
            }
        }
    }
    return st.empty();
}

int main() {
    cout << isBalanced("a+(b*c)-{d/e}") << endl;     
    cout << isBalanced("( [ ) ]") << endl;           
    cout << isBalanced("{[()]}") << endl;            
    cout << isBalanced("3*(6+[3-6])") << endl;
}