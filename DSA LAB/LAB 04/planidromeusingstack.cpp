#include <iostream>
#include <stack>
using namespace std;

int main() {
    string s;
    cout << "Enter a string: ";
    cin >> s;

    stack<char> st;

    // Push all characters into stack
    for(int i = 0; i < s.length(); i++) {
        st.push(s[i]);
    }

    // Compare string with characters popped from stack
    bool palindrome = true;

    for(int i = 0; i < s.length(); i++) {
        if(s[i] != st.top()) {
            palindrome = false;
            break;
        }
        st.pop();
    }

    if(palindrome)
        cout << "The string is a palindrome.";
    else
        cout << "The string is not a palindrome.";

    return 0;
}