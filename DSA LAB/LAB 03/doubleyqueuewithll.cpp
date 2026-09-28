#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* prev;  
    Node* next;  

    Node(int value) {
        data = value;
        prev = NULL;
        next = NULL;
    }
};

class Deque {
private:
    Node* front;  
    Node* rear;   

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
            front = rear = n;      
        } else {
            n->next = front;        
            front->prev = n;        
            front = n;              
        }
    }

    void insertRear(int value) {
        Node* n = new Node(value);
        if (isEmpty()) {
            front = rear = n;
        } else {
            n->prev = rear;         
            rear->next = n;         
            rear = n;               
        }
    }

    void deleteFront() {
        if (isEmpty()) {
            cout << "Deque is empty\n";
            return;
        }
        Node* temp = front;
        front = front->next;        
        if (front == NULL)
            rear = NULL;          
        else
            front->prev = NULL;    
        delete temp;
    }

    void deleteRear() {
        if (isEmpty()) {
            cout << "Deque is empty\n";
            return;
        }
        Node* temp = rear;
        rear = rear->prev;         
        if (rear == NULL)
            front = NULL;          
        else
            rear->next = NULL;    
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