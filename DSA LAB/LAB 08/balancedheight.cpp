#include <iostream>
#include <algorithm>
using namespace std;
struct Node {
    int val;
    Node* left;
    Node* right;

    Node(int x) {
        val = x;
        left = nullptr;
        right = nullptr;
    }
};

int checkHeight(Node* root) {
  
    if (root == nullptr) return 0;

    int leftHeight = checkHeight(root->left);
    if (leftHeight == -1) return -1; 

    int rightHeight = checkHeight(root->right);
    if (rightHeight == -1) return -1; 

    if (abs(leftHeight - rightHeight) > 1) {
        return -1;
    }

    return 1 + max(leftHeight, rightHeight);
}

bool isBalanced(Node* root) {
    return checkHeight(root) != -1;
}

int main() {

    Node* root1 = new Node(3);
    root1->left = new Node(9);
    root1->right = new Node(20);
    root1->right->left = new Node(15);
    root1->right->right = new Node(7);

    cout << "Example 1 Output: " << (isBalanced(root1) ? "true" : "false") << endl; // true

    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->right = new Node(2);
    root2->left->left = new Node(3);
    root2->left->right = new Node(3);
    root2->left->left->left = new Node(4);
    root2->left->left->right = new Node(4);

    cout << "Example 2 Output: " << (isBalanced(root2) ? "true" : "false") << endl; // false

    return 0;
}