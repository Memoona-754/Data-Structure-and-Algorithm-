#include <iostream>
using namespace std;

int main() {
    int arr[3][4] = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };

    int R = 3, C = 4;
    int rowMajor[12], colMajor[12];
    int k = 0;

    // ---- Row Major: outer = rows, inner = columns ----
    k = 0;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            rowMajor[k++] = arr[i][j];

    // ---- Column Major: outer = columns, inner = rows ----
    k = 0;
    for (int j = 0; j < C; j++)
        for (int i = 0; i < R; i++)
            colMajor[k++] = arr[i][j];

    // ---- Print both ----
    cout << "Row Major:    ";
    for (int x = 0; x < R * C; x++)
        cout << rowMajor[x] << " ";
    cout << endl;

    cout << "Column Major: ";
    for (int x = 0; x < R * C; x++)
        cout << colMajor[x] << " ";
    cout << endl;

    return 0;
}