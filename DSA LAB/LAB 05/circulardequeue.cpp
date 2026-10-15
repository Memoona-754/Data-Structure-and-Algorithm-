
#include <iostream>
using namespace std;

class MyCircularDeque {
private:
    int *arr;
    int capacity;
    int front;
    int rear;
    int count;

public:
    MyCircularDeque(int k) {
        capacity = k;
        arr = new int[k];
        front = 0;
        rear = -1;
        count = 0;
    }

    bool insertFront(int value) {
        if (isFull())
            return false;

        if (isEmpty()) {
            front = 0;
            rear = 0;
        } else {
            front = (front - 1 + capacity) % capacity;
        }

        arr[front] = value;
        count++;
        return true;
    }

    bool insertLast(int value) {
        if (isFull())
            return false;

        if (isEmpty()) {
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % capacity;
        }

        arr[rear] = value;
        count++;
        return true;
    }

    bool deleteFront() {
        if (isEmpty())
            return false;

        front = (front + 1) % capacity;
        count--;

        if (count == 0) {
            front = 0;
            rear = -1;
        }

        return true;
    }

    bool deleteLast() {
        if (isEmpty())
            return false;

        rear = (rear - 1 + capacity) % capacity;
        count--;

        if (count == 0) {
            front = 0;
            rear = -1;
        }

        return true;
    }

    int getFront() {
        if (isEmpty())
            return -1;

        return arr[front];
    }

    int getRear() {
        if (isEmpty())
            return -1;

        return arr[rear];
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == capacity;
    }

    ~MyCircularDeque() {
        delete[] arr;
    }
};

int main() {
    MyCircularDeque myCircularDeque(3);

    cout << boolalpha;

    cout << myCircularDeque.insertLast(1) << endl;  
    cout << myCircularDeque.insertLast(2) << endl;  
    cout << myCircularDeque.insertFront(3) << endl; 
    cout << myCircularDeque.insertFront(4) << endl; 

    cout << myCircularDeque.getRear() << endl;      
    cout << myCircularDeque.isFull() << endl;       
    cout << myCircularDeque.deleteLast() << endl;   
    cout << myCircularDeque.insertFront(4) << endl; 
    cout << myCircularDeque.getFront() << endl;     

    return 0;
}
