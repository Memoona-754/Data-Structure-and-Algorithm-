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

struct RobResult {
    int rob;
    int notRob;
};
RobResult robHelper(Node* root) {

    if (root == nullptr) {
        return {0, 0};
    }
    RobResult left = robHelper(root->left);
    RobResult right = robHelper(root->right);

    RobResult current;

    current.rob = root->val + left.notRob + right.notRob;
    current.notRob = max(left.rob, left.notRob) + max(right.rob, right.notRob);

    return current;
}

int rob(Node* root) {
    RobResult result = robHelper(root);

    return max(result.rob, result.notRob);
}

int main() {
    Node* root1 = new Node(3);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->right = new Node(3);
    root1->right->right = new Node(1);

    cout << "Example 1 Output: " << rob(root1) << endl; 

    Node* root2 = new Node(3);
    root2->left = new Node(4);
    root2->right = new Node(5);
    root2->left->left = new Node(1);
    root2->left->right = new Node(3);
    root2->right->right = new Node(1);

    cout << "Example 2 Output: " << rob(root2) << endl; 

    return 0;
}