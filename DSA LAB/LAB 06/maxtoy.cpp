#include <iostream>
#include <algorithm>
using namespace std;

int maxToys(int arr[], int n, int k) {
    sort(arr, arr + n);         

    int count = 0;
    int spent = 0;
    for (int i = 0; i < n; i++) {
        if (spent + arr[i] <= k) {
            spent += arr[i];
            count++;
        } else {
            break;              
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 12, 5, 111, 200, 1000, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 50;

    cout << maxToys(arr, n, k) << endl;   
    return 0;
}