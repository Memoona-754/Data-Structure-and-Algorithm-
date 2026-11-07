#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
public:
    Node* root;

    BinaryTree() {
        root = nullptr;
    }

    bool search(Node* current, int val) {
        if (current == nullptr) {
            return false; 
        }
        if (current->data == val) {
            return true;  
        }
        return search(current->left, val) || search(current->right, val);
    }

    void preOrder(Node* current) {
        if (current == nullptr) return;

        cout << current->data << " "; 
        preOrder(current->left);    
        preOrder(current->right);    
    }

    void postOrder(Node* current) {
        if (current == nullptr) return;

        postOrder(current->left);     
        postOrder(current->right);   
        cout << current->data << " "; 
    }
};

int main() {
    BinaryTree tree;

    tree.root = new Node(1);
    tree.root->left = new Node(2);
    tree.root->right = new Node(3);
    tree.root->left->left = new Node(4);
    tree.root->left->right = new Node(5);

    // --- Pre-order Traversal ---
    cout << "Pre-order Traversal: ";
    tree.preOrder(tree.root);
    cout << endl; // Output: 1 2 4 5 3

    // --- Post-order Traversal ---
    cout << "Post-order Traversal: ";
    tree.postOrder(tree.root);
    cout << endl; // Output: 4 5 2 3 1

    // --- Search Operation ---
    int target = 4;
    if (tree.search(tree.root, target)) {
        cout << target << " found in the tree." << endl;
    } else {
        cout << target << " not found in the tree." << endl;
    }

    target = 99;
    if (tree.search(tree.root, target)) {
        cout << target << " found in the tree." << endl;
    } else {
        cout << target << " not found in the tree." << endl;
    }

    return 0;
}