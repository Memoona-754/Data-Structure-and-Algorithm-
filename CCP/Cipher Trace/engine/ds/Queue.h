// engine/ds/Queue.h
#pragma once
#include <stdexcept>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };

    Node* frontNode;
    Node* rearNode;
    int count;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr), count(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Rule of Three: prevent shallow copy double-free
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    // Enqueue at rear: O(1)
    void enqueue(const T& value) {
        Node* n = new Node(value);
        if (isEmpty()) {
            frontNode = n;
            rearNode = n;
        } else {
            rearNode->next = n;
            rearNode = n;
        }
        count++;
    }

    // Dequeue from front: O(1)
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        Node* temp = frontNode;
        T value = temp->data;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            rearNode = nullptr; // Reset rear when queue becomes empty to prevent dangling pointer
        }
        delete temp;
        count--;
        return value;
    }

    // Inspect front item: O(1)
    const T& front() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return frontNode->data;
    }

    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};
