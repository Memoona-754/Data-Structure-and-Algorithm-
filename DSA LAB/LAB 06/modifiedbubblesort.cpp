#include <iostream>
using namespace std;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    printArray(arr, n);

    bubbleSort(arr, n);

    cout << "Sorted array:   ";
    printArray(arr, n);

    int sorted[] = {1, 2, 3, 4, 5};
    int m = sizeof(sorted) / sizeof(sorted[0]);

    cout << "\nAlready sorted: ";
    printArray(sorted, m);
    bubbleSort(sorted, m);
    cout << "After sorting:  ";
    printArray(sorted, m);

    return 0;
}