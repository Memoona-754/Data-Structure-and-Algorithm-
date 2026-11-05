#include <iostream>
#include <vector>
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

int preIndex = 0;

int findIndex(vector<int>& inorder, int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == value) {
            return i;
        }
    }
    return -1;
}

Node* buildTreeHelper(vector<int>& preorder, vector<int>& inorder, int inStart, int inEnd) {
 
    if (inStart > inEnd) {
        return nullptr;
    }

    int rootVal = preorder[preIndex++];
    Node* root = new Node(rootVal);

    int inIndex = findIndex(inorder, inStart, inEnd, rootVal);

    root->left = buildTreeHelper(preorder, inorder, inStart, inIndex - 1);

    root->right = buildTreeHelper(preorder, inorder, inIndex + 1, inEnd);

    return root;
}

Node* buildTree(vector<int>& preorder, vector<int>& inorder) {
    preIndex = 0; 
    return buildTreeHelper(preorder, inorder, 0, inorder.size() - 1);
}

void printPreorder(Node* root) {
    if (root == nullptr) return;
    cout << root->val << " ";
    printPreorder(root->left);
    printPreorder(root->right);
}

int main() {
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder  = {9, 3, 15, 20, 7};

    Node* root = buildTree(preorder, inorder);

    cout << "Preorder of constructed tree: ";
    printPreorder(root);
    cout << endl; 

    return 0;
}