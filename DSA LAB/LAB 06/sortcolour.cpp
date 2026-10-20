#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int low = 0;              
        int mid = 0;                 
        int high = nums.size() - 1;  

        while (mid <= high) {
            if (nums[mid] == 0) {
                swap(nums[low], nums[mid]);
                low++;
                mid++;
            } else if (nums[mid] == 1) {
                mid++;
            } else {               
                swap(nums[mid], nums[high]);
                high--;              
            }
        }
    }
};

void printArray(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << (i + 1 < v.size() ? "," : "");
    }
    cout << "]" << endl;
}

int main() {
    Solution s;

    vector<int> a = {2, 0, 2, 1, 1, 0};
    s.sortColors(a);
    printArray(a);  

    vector<int> b = {2, 0, 1};
    s.sortColors(b);
    printArray(b);  

    return 0;
}