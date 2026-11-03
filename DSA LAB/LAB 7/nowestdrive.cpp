#include <iostream>
#include <vector>
using namespace std;

bool carPooling(vector<vector<int>>& trips, int capacity) {
    int stops[1001] = {0};

    for (auto trip : trips) {
        int passengers = trip[0];
        int from = trip[1];
        int to = trip[2];

        stops[from] += passengers; 
        stops[to] -= passengers;   
    }

    int currentPassengers = 0;
    for (int i = 0; i <= 1000; i++) {
        currentPassengers += stops[i];

        if (currentPassengers > capacity) {
            return false;
        }
    }

    return true; 
}

int main() {
    vector<vector<int>> trips1 = {{2, 1, 5}, {3, 3, 7}};
    int capacity1 = 4;
    cout << "Example 1: " << (carPooling(trips1, capacity1) ? "true" : "false") << endl; 

    vector<vector<int>> trips2 = {{2, 1, 5}, {3, 3, 7}};
    int capacity2 = 5;
    cout << "Example 2: " << (carPooling(trips2, capacity2) ? "true" : "false") << endl; 

    return 0;
}