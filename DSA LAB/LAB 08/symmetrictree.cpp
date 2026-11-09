#include <iostream>
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

bool isMirror(Node* t1, Node* t2) {
    // If both are NULL, they are mirrors
    if (t1 == nullptr && t2 == nullptr) return true;

    if (t1 == nullptr || t2 == nullptr) return false;

    return (t1->val == t2->val) &&
           isMirror(t1->left, t2->right) &&
           isMirror(t1->right, t2->left);
}

bool isSymmetric(Node* root) {
    if (root == nullptr) return true;
    return isMirror(root->left, root->right);
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(2);

    root->left->left = new Node(3);
    root->left->right = new Node(4);

    root->right->left = new Node(4);
    root->right->right = new Node(3);

    if (isSymmetric(root)) {
        cout << "Output: true" << endl;
    } else {
        cout << "Output: false" << endl;
    }

    return 0;
}