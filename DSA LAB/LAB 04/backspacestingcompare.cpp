#include <iostream>
#include <stack>
using namespace std;

string processString(string s) {
    stack<char> st;

    for(int i = 0; i < s.length(); i++) {

        if(s[i] == '#') {
            // Backspace
            if(!st.empty()) {
                st.pop();
            }
        }
        else {
            st.push(s[i]);
        }
    }

    string result = "";

    while(!st.empty()) {
        result = st.top() + result;
        st.pop();
    }

    return result;
}

int main() {

    string s, t;

    cout << "Enter first string: ";
    cin >> s;

    cout << "Enter second string: ";
    cin >> t;

    string result1 = processString(s);
    string result2 = processString(t);

    if(result1 == result2)
        cout << "true";
    else
        cout << "false";

    return 0;
}