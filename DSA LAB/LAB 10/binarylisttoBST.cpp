#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode(int x) {
        val = x;
        next = NULL;
    }
};

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
    TreeNode* sortedListToBST(ListNode* head) {
        if (head == NULL)
            return NULL;

        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* prev = NULL;

        // Find middle node
        while (fast != NULL && fast->next != NULL) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        // Break left half
        if (prev != NULL)
            prev->next = NULL;

        // Middle becomes root
        TreeNode* root = new TreeNode(slow->val);

        // Build left subtree
        if (head != slow)
            root->left = sortedListToBST(head);

        // Build right subtree
        root->right = sortedListToBST(slow->next);

        return root;
    }
};

// Preorder: Root, Left, Right
void preorder(TreeNode* root) {
    if (root == NULL)
        return;

    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

// Create linked list
ListNode* createList(int arr[], int n) {
    ListNode* head = new ListNode(arr[0]);
    ListNode* temp = head;

    for (int i = 1; i < n; i++) {
        temp->next = new ListNode(arr[i]);
        temp = temp->next;
    }

    return head;
}

int main() {
    int arr[] = {-10, -3, 0, 5, 9};
    int n = 5;

    ListNode* head = createList(arr, n);

    Solution obj;
    TreeNode* root = obj.sortedListToBST(head);

    cout << "Preorder traversal: ";
    preorder(root);

    return 0;
}