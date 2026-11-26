#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {
        val = x;
        left = NULL;
        right = NULL;
    }
};

class Solution {
public:
    TreeNode* build(vector<int>& nums, int left, int right) {
        if (left > right)
            return NULL;

        int mid = left + (right - left) / 2;

        TreeNode* root = new TreeNode(nums[mid]);

        root->left = build(nums, left, mid - 1);
        root->right = build(nums, mid + 1, right);

        return root;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return build(nums, 0, nums.size() - 1);
    }
};

// Print tree in preorder (Root, Left, Right)
void preorder(TreeNode* root) {
    if (root == NULL)
        return;

    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

int main() {
    vector<int> nums = {-10, -3, 0, 5, 9};

    Solution obj;
    TreeNode* root = obj.sortedArrayToBST(nums);

    cout << "Preorder traversal: ";
    preorder(root);

    return 0;
}