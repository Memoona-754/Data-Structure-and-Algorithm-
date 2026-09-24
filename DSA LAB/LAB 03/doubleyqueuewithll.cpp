#include <iostream>
using namespace std;

// One box of the list: holds a value + two arrows
class Node {
public:
    int data;
    Node* prev;   // arrow to the box before
    Node* next;   // arrow to the box after

    Node(int value) {
        data = value;
        prev = NULL;
        next = NULL;
    }
};

class Deque {
private:
    Node* front;  // first box
    Node* rear;   // last box

public:
    Deque() {
        front = NULL;
        rear = NULL;
    }

    bool isEmpty() {
        return front == NULL;
    }

    void insertFront(int value) {
        Node* n = new Node(value);
        if (isEmpty()) {
            front = rear = n;       // only one box, so it is both front and rear
        } else {
            n->next = front;        // new box points forward to old front
            front->prev = n;        // old front points back to new box
            front = n;              // new box is now the front
        }
    }

    void insertRear(int value) {
        Node* n = new Node(value);
        if (isEmpty()) {
            front = rear = n;
        } else {
            n->prev = rear;         // new box points back to old rear
            rear->next = n;         // old rear points forward to new box
            rear = n;               // new box is now the rear
        }
    }

    void deleteFront() {
        if (isEmpty()) {
            cout << "Deque is empty\n";
            return;
        }
        Node* temp = front;
        front = front->next;        // move front one step forward
        if (front == NULL)
            rear = NULL;            // list became empty
        else
            front->prev = NULL;     // new front has nothing before it
        delete temp;
    }

    void deleteRear() {
        if (isEmpty()) {
            cout << "Deque is empty\n";
            return;
        }
        Node* temp = rear;
        rear = rear->prev;          // move rear one step back (easy because of prev!)
        if (rear == NULL)
            front = NULL;           // list became empty
        else
            rear->next = NULL;      // new rear has nothing after it
        delete temp;
    }

    void display() {
        Node* cur = front;
        while (cur != NULL) {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << endl;
    }
};

int main() {
    Deque d;
    d.insertRear(10);
    d.insertRear(20);
    d.insertFront(5);
    d.display();      // 5 10 20

    d.deleteFront();
    d.display();      // 10 20

    d.deleteRear();
    d.display();      // 10

    return 0;
}