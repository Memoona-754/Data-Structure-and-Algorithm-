#include <iostream>
#include <vector>
#include <algorithm> // for sort and max
using namespace std;

int findLHS(vector<int>& nums) {

    sort(nums.begin(), nums.end());

    int left = 0;
    int maxLength = 0;

    for (int right = 0; right < nums.size(); right++) {
        
        while (nums[right] - nums[left] > 1) {
            left++;
        }
        if (nums[right] - nums[left] == 1) {
            maxLength = max(maxLength, right - left + 1);
        }
    }

    return maxLength;
}

int main() {
    vector<int> nums1 = {1, 3, 2, 2, 5, 2, 3, 7};
    cout << "Example 1 Output: " << findLHS(nums1) << endl;

    vector<int> nums2 = {1, 2, 3, 4};
    cout << "Example 2 Output: " << findLHS(nums2) << endl;

    vector<int> nums3 = {1, 1, 1, 1};
    cout << "Example 3 Output: " << findLHS(nums3) << endl; 

    return 0;
}