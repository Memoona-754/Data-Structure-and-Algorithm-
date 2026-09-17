#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int x) : val(x), next(nullptr) {}
};

class Stack {
private:
    Node* top;
    int count;

public:
    Stack() {
        top = nullptr;
        count = 0;
    }

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
        count++;
    }

    bool pop() {
        if (isEmpty()) return false;

        Node* oldTop = top;
        top = top->next;
        delete oldTop;
        count--;
        return true;
    }

    int peek() {
        if (isEmpty()) return -1;
        return top->val;
    }

    bool isEmpty() {
        return count == 0;
    }

    int size() {
        return count;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

int main() {
    Stack s;

    cout << (s.isEmpty() ? "true" : "false") << endl; 

    s.push(1);
    s.push(2);
    s.push(3);

    cout << "size: " << s.size() << endl;   // 3
    cout << "peek: " << s.peek() << endl;   // 3

    cout << (s.pop() ? "true" : "false") << endl; // true (removed 3)
    cout << "peek: " << s.peek() << endl;   // 2
    cout << "size: " << s.size() << endl;   // 2

    s.push(4);
    cout << "peek: " << s.peek() << endl;   // 4
    cout << "size: " << s.size() << endl;   // 3

    return 0;
}