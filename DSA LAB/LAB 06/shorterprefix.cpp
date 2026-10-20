#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> pancakeSort(vector<int>& arr) {
        vector<int> flips;
        int n = arr.size();

        for (int size = n; size > 1; size--) {
            int maxIdx = max_element(arr.begin(), arr.begin() + size) - arr.begin();

            if (maxIdx == size - 1) continue;      

            if (maxIdx != 0) {                    
                reverse(arr.begin(), arr.begin() + maxIdx + 1);
                flips.push_back(maxIdx + 1);
            }
            reverse(arr.begin(), arr.begin() + size); 
            flips.push_back(size);
        }
        return flips;
    }
};

int main() {
    vector<int> arr = {3, 2, 4, 1};
    Solution s;
    vector<int> flips = s.pancakeSort(arr);

    cout << "Flips: ";
    for (int k : flips) cout << k << " ";
    cout << endl;

    cout << "Array after flips: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    return 0;
}