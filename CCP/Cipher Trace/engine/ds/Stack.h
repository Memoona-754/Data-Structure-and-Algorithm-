// engine/ds/Stack.h
#pragma once
#include <stdexcept>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n) : data(d), next(n) {}
    };

    Node* topNode;
    int count;

public:
    Stack() : topNode(nullptr), count(0) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Rule of Three: forbid naive shallow copying to prevent double-free crashes
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    // Push item onto stack: O(1)
    void push(const T& value) {
        Node* n = new Node(value, topNode);
        topNode = n;
        count++;
    }

    // Pop item from top: O(1)
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        Node* temp = topNode;
        T value = temp->data;
        topNode = topNode->next;
        delete temp;
        count--;
        return value;
    }

    // Inspect top item without removing: O(1)
    const T& peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return topNode->data;
    }

    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};
