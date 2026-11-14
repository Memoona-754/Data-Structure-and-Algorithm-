// MaxHeap.h
#pragma once
#include <vector>
#include <utility>
#include <stdexcept>
#include "Rule.h"

// Custom Binary Max-Heap Template (Array-based, complete binary tree)
// Root is always the maximum element
template <typename T, typename Compare>
class MaxHeap {
private:
    std::vector<T> heap;
    Compare comp;

    int parent(int i) const { return (i - 1) / 2; }
    int left(int i)   const { return 2 * i + 1; }
    int right(int i)  const { return 2 * i + 2; }

    void heapifyUp(int i) {
        while (i > 0 && comp(heap[parent(i)], heap[i])) {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int largest = i;
        int l = left(i);
        int r = right(i);

        if (l < (int)heap.size() && comp(heap[largest], heap[l])) {
            largest = l;
        }
        if (r < (int)heap.size() && comp(heap[largest], heap[r])) {
            largest = r;
        }

        if (largest != i) {
            std::swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    MaxHeap(Compare c = Compare()) : comp(c) {}

    // Insert element into heap: O(log N)
    void insert(const T& item) {
        heap.push_back(item);
        heapifyUp((int)heap.size() - 1);
    }

    // Extract maximum element: O(log N)
    T extractMax() {
        if (isEmpty()) {
            throw std::runtime_error("Heap is empty");
        }
        T maxItem = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!isEmpty()) {
            heapifyDown(0);
        }
        return maxItem;
    }

    // Inspect maximum element: O(1)
    const T& peekMax() const {
        if (isEmpty()) {
            throw std::runtime_error("Heap is empty");
        }
        return heap[0];
    }

    bool isEmpty() const { return heap.empty(); }
    int size() const { return (int)heap.size(); }
};

// Comparator for Evidence: max-heap ordered by highest threat weight
struct EvidenceWeightComparator {
    bool operator()(const Evidence& a, const Evidence& b) const {
        return a.weight < b.weight; // b has higher priority than a
    }
};
