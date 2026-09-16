#include <iostream>
using namespace std;
int BinarySearch(int arr[], int l, int r, int x) {
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] == x)
            return m;
        if (arr[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}
int main() {
    int R = 3;
    int C = 4;
    int arr[R][C] = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    int temp[R * C];
    int k = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            temp[k] = arr[i][j];
            k++;
        } }
    int p = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cout << temp[p] << " ";
            p++;
        }
    }
    cout << endl;
    int n = sizeof(temp) / sizeof(temp[0]);
    int result = BinarySearch(temp, 0, n - 1, 3);
    if (result == -1) {
        cout << "False" << endl;
    } else {
        cout << "True at index " << result;
    }
    return 0;
}