#include <iostream>
#include <stack>
using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
};

void preorder(Node* root)
{
    if (root == NULL)
        return;

    stack<Node*> s;
    s.push(root);

    while (!s.empty())
    {
        Node* temp = s.top();
        s.pop();

        cout << temp->data << " ";

        if (temp->right != NULL)
            s.push(temp->right);

        if (temp->left != NULL)
            s.push(temp->left);
    }
}
void postorder(Node* root)
{
    if (root == NULL)
        return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty())
    {
        Node* temp = s1.top();
        s1.pop();

        s2.push(temp);

        if (temp->left != NULL)
            s1.push(temp->left);

        if (temp->right != NULL)
            s1.push(temp->right);
    }

    while (!s2.empty())
    {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}
int main()
{
    Node* root = new Node{1, NULL, NULL};
    root->left = new Node{2, NULL, NULL};
    root->right = new Node{3, NULL, NULL};
    root->left->left = new Node{4, NULL, NULL};
    root->left->right = new Node{5, NULL, NULL};

    cout << "Preorder Traversal: ";
    preorder(root);

    cout << "\nPostorder Traversal: ";
    postorder(root);

    return 0;
}