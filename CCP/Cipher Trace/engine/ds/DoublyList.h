// engine/ds/DoublyList.h
#pragma once
#include <stdexcept>

template <typename T>
class DoublyList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    Node* cursor;
    int count;

public:
    DoublyList() : head(nullptr), tail(nullptr), cursor(nullptr), count(0) {}

    ~DoublyList() {
        clear();
    }

    DoublyList(const DoublyList&) = delete;
    DoublyList& operator=(const DoublyList&) = delete;

    void clear() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
        head = tail = cursor = nullptr;
        count = 0;
    }

    void append(const T& value) {
        Node* n = new Node(value);
        if (isEmpty()) {
            head = tail = cursor = n;
        } else {
            tail->next = n;
            n->prev = tail;
            tail = n;
            cursor = n;
        }
        count++;
    }

    bool movePrevious() {
        if (cursor != nullptr && cursor->prev != nullptr) {
            cursor = cursor->prev;
            return true;
        }
        return false;
    }

    bool moveNext() {
        if (cursor != nullptr && cursor->next != nullptr) {
            cursor = cursor->next;
            return true;
        }
        return false;
    }

    const T& getCurrent() const {
        if (cursor == nullptr) {
            throw std::runtime_error("DoublyList cursor is null or empty");
        }
        return cursor->data;
    }

    bool hasPrevious() const { return cursor != nullptr && cursor->prev != nullptr; }
    bool hasNext() const { return cursor != nullptr && cursor->next != nullptr; }
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};
