// CircularBuffer.h
#pragma once
#include <vector>
#include <stdexcept>

template <typename T>
class CircularBuffer {
private:
    T* buffer;
    int capacity;
    int head; // Points to oldest element
    int tail; // Points to next available insertion slot
    int count;

public:
    explicit CircularBuffer(int cap = 10) 
        : capacity(cap), head(0), tail(0), count(0) {
        if (capacity <= 0) {
            capacity = 10;
        }
        buffer = new T[capacity];
    }

    ~CircularBuffer() {
        delete[] buffer;
    }

    // Rule of Three: forbid shallow copy
    CircularBuffer(const CircularBuffer&) = delete;
    CircularBuffer& operator=(const CircularBuffer&) = delete;

    // Add element: O(1). If full, automatically overwrites the oldest element!
    void push(const T& item) {
        buffer[tail] = item;
        tail = (tail + 1) % capacity;

        if (count < capacity) {
            count++;
        } else {
            // Buffer was full; oldest item at head was overwritten, so advance head
            head = (head + 1) % capacity;
        }
    }

    // Get all items in chronological order (from oldest to newest)
    std::vector<T> toVector() const {
        std::vector<T> items;
        items.reserve(count);
        for (int i = 0; i < count; i++) {
            int index = (head + i) % capacity;
            items.push_back(buffer[index]);
        }
        return items;
    }

    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == capacity; }
    int size() const { return count; }
    int getCapacity() const { return capacity; }
};
