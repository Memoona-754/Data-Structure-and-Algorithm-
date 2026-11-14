// Sorting.h
#pragma once
#include <vector>
#include <utility>
#include "Rule.h"

struct SortStats {
    long long comparisons;
    long long swaps;
    SortStats() : comparisons(0), swaps(0) {}
    void reset() { comparisons = 0; swaps = 0; }
};

class SortingSuite {
public:
    // ==========================================================
    // 1. MERGE SORT: O(N log N) - Stable Divide-and-Conquer
    // ==========================================================
    static void mergeSort(std::vector<Evidence>& arr, SortStats& stats) {
        if (arr.size() <= 1) return;
        std::vector<Evidence> temp(arr.size());
        mergeSortInternal(arr, temp, 0, (int)arr.size() - 1, stats);
    }

    // ==========================================================
    // 2. QUICK SORT: O(N log N) avg - In-place Partitioning
    // ==========================================================
    static void quickSort(std::vector<Evidence>& arr, SortStats& stats) {
        if (arr.size() <= 1) return;
        quickSortInternal(arr, 0, (int)arr.size() - 1, stats);
    }

    // ==========================================================
    // 3. BUBBLE SORT: O(N^2) - Baseline for Algorithm Lab
    // ==========================================================
    static void bubbleSort(std::vector<Evidence>& arr, SortStats& stats) {
        int n = (int)arr.size();
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                stats.comparisons++;
                // Sort descending: highest severity weight first
                if (arr[j].weight < arr[j + 1].weight) {
                    std::swap(arr[j], arr[j + 1]);
                    stats.swaps++;
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }

private:
    static void mergeSortInternal(std::vector<Evidence>& arr, std::vector<Evidence>& temp,
                                  int left, int right, SortStats& stats) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSortInternal(arr, temp, left, mid, stats);
        mergeSortInternal(arr, temp, mid + 1, right, stats);
        merge(arr, temp, left, mid, right, stats);
    }

    static void merge(std::vector<Evidence>& arr, std::vector<Evidence>& temp,
                      int left, int mid, int right, SortStats& stats) {
        int i = left;
        int j = mid + 1;
        int k = left;

        while (i <= mid && j <= right) {
            stats.comparisons++;
            // Sort descending: higher weight comes first
            if (arr[i].weight >= arr[j].weight) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
            stats.swaps++;
        }

        while (i <= mid) {
            temp[k++] = arr[i++];
            stats.swaps++;
        }

        while (j <= right) {
            temp[k++] = arr[j++];
            stats.swaps++;
        }

        for (int p = left; p <= right; p++) {
            arr[p] = temp[p];
        }
    }

    static void quickSortInternal(std::vector<Evidence>& arr, int low, int high, SortStats& stats) {
        if (low < high) {
            int pi = partition(arr, low, high, stats);
            quickSortInternal(arr, low, pi - 1, stats);
            quickSortInternal(arr, pi + 1, high, stats);
        }
    }

    static int partition(std::vector<Evidence>& arr, int low, int high, SortStats& stats) {
        int pivotWeight = arr[high].weight;
        int i = low - 1;

        for (int j = low; j < high; j++) {
            stats.comparisons++;
            // Sort descending: larger or equal weight before smaller
            if (arr[j].weight >= pivotWeight) {
                i++;
                std::swap(arr[i], arr[j]);
                stats.swaps++;
            }
        }
        std::swap(arr[i + 1], arr[high]);
        stats.swaps++;
        return i + 1;
    }
};
