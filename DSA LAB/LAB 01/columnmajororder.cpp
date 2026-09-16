#include <iostream>
using namespace std;

int main() {
    const int R = 3, C = 4;

    int arr[R][C] = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };

    int temp[R * C];  
    int k = 0;

    for (int j = 0; j < C; j++) {
        for (int i = 0; i < R; i++) {
            temp[k] = arr[i][j];
            k++;
        }
    }

    cout << "Original 2D Array:" << endl;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\n1D Array (Column Major Order): ";
    for (int x = 0; x < R * C; x++) {
        cout << temp[x] << " ";
    }
    cout << endl;

    return 0;
}