#include <iostream>
using namespace std;

int main() {
    int **arr = new int*[3];   // Step 1
    int Size[3];                // Step 2
    int i, j;

    // Step 3: Input phase — ask size of each row, allocate that row
    for (i = 0; i < 3; i++) {
        cout << "Row " << i + 1 << " size: ";
        cin >> Size[i];
        arr[i] = new int[Size[i]];
    }

    // Step 4: Fill each row with Size[i] elements
    for (i = 0; i < 3; i++) {
        for (j = 0; j < Size[i]; j++) {
            cout << "Enter row " << i + 1 << " element " << j + 1 << ": ";
            cin >> *(*(arr + i) + j);   // same as arr[i][j]
        }
    }

    // Step 5: Print the jagged array
    cout << "\nJagged Array:\n";
    for (i = 0; i < 3; i++) {
        for (j = 0; j < Size[i]; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    // Step 6: Deallocate memory (rows first, then the pointer array)
    for (i = 0; i < 3; i++) {
        delete[] arr[i];
    }
    delete[] arr;

    return 0;
}