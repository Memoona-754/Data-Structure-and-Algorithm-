#include <iostream>
using namespace std;

int search(int nums[], int n, int target) {
    int l = 0, r = n - 1;

    while (l <= r) {
        int m = l + (r - l) / 2;

        if (nums[m] == target)
            return m;

        if (nums[m] < target)
            l = m + 1;
        else
            r = m - 1;
    }

    return -1;   // not found
}

int main() {
    int nums[] = {-1, 0, 3, 5, 9, 12};
    int n = sizeof(nums) / sizeof(nums[0]);

    int target1 = 9;
    cout << "Search " << target1 << ": " << search(nums, n, target1) << endl;   // expect 4

    int target2 = 2;
    cout << "Search " << target2 << ": " << search(nums, n, target2) << endl;   // expect -1

    return 0;
}