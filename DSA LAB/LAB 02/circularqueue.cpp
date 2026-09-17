#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int x) : val(x), next(nullptr) {}
};

class MyCircularQueue {
private:
    Node* head;
    Node* tail;
    int count;
    int capacity;

public:
    MyCircularQueue(int k) {
        head = nullptr;
        tail = nullptr;
        count = 0;
        capacity = k;
    }

    bool enQueue(int value) {
        if (isFull()) return false;

        Node* newNode = new Node(value);
        if (isEmpty()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        tail->next = head; 
        count++;
        return true;
    }

    bool deQueue() {
        if (isEmpty()) return false;

        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            Node* oldHead = head;
            head = head->next;
            tail->next = head; 
            delete oldHead;
        }
        count--;
        return true;
    }

    int Front() {
        if (isEmpty()) return -1;
        return head->val;
    }

    int Rear() {
        if (isEmpty()) return -1;
        return tail->val;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == capacity;
    }

    ~MyCircularQueue() {
        if (isEmpty()) return;
        Node* curr = head;
        for (int i = 0; i < count; i++) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
};

int main() {
    MyCircularQueue cq(3);

    cout << (cq.enQueue(1) ? "true" : "false") << endl; // true
    cout << (cq.enQueue(2) ? "true" : "false") << endl; // true
    cout << (cq.enQueue(3) ? "true" : "false") << endl; // true
    cout << (cq.enQueue(4) ? "true" : "false") << endl; // false, queue is full
    cout << cq.Rear() << endl;                          // 3
    cout << (cq.isFull() ? "true" : "false") << endl;   // true
    cout << (cq.deQueue() ? "true" : "false") << endl;  // true
    cout << (cq.enQueue(4) ? "true" : "false") << endl; // true
    cout << cq.Rear() << endl;                          // 4

    return 0;
}