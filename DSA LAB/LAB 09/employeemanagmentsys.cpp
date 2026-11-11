
#include <iostream>
#include <string>
using namespace std;

class EmployeeNode
{
public:
    int id;
    string name;
    string department;

    EmployeeNode* left;
    EmployeeNode* right;

    EmployeeNode(int i, string n, string d)
    {
        id = i;
        name = n;
        department = d;
        left = NULL;
        right = NULL;
    }
};

class EmployeeBST
{
private:
    EmployeeNode* root;

    EmployeeNode* insertNode(EmployeeNode* node, int id,
                             string name, string department)
    {
        if (node == NULL)
            return new EmployeeNode(id, name, department);

        if (id < node->id)
            node->left = insertNode(node->left, id, name, department);

        else if (id > node->id)
            node->right = insertNode(node->right, id, name, department);

        else
            cout << "Duplicate Employee ID not allowed!\n";

        return node;
    }

    EmployeeNode* searchNode(EmployeeNode* node, int id)
    {
        if (node == NULL || node->id == id)
            return node;

        if (id < node->id)
            return searchNode(node->left, id);

        return searchNode(node->right, id);
    }
    EmployeeNode* minimum(EmployeeNode* node)
    {
        while (node != NULL && node->left != NULL)
            node = node->left;

        return node;
    }

    EmployeeNode* maximum(EmployeeNode* node)
    {
        while (node != NULL && node->right != NULL)
            node = node->right;

        return node;
    }

    EmployeeNode* deleteHelper(EmployeeNode* node, int id)
    {
        if (node == NULL)
            return NULL;

        if (id < node->id)
            node->left = deleteHelper(node->left, id);

        else if (id > node->id)
            node->right = deleteHelper(node->right, id);

        else
        {
            if (node->left == NULL && node->right == NULL)
            {
                delete node;
                return NULL;
            }

            else if (node->left == NULL)
            {
                EmployeeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == NULL)
            {
                EmployeeNode* temp = node->left;
                delete node;
                return temp;
            }
            else
            {
                EmployeeNode* temp = minimum(node->right);

                node->id = temp->id;
                node->name = temp->name;
                node->department = temp->department;

                node->right = deleteHelper(node->right, temp->id);
            }
        }

        return node;
    }

    void inorder(EmployeeNode* node)
    {
        if (node == NULL)
            return;

        inorder(node->left);

        cout << "ID: " << node->id
             << " | Name: " << node->name
             << " | Department: " << node->department << endl;

        inorder(node->right);
    }

public:

    EmployeeBST()
    {
        root = NULL;
    }
    void insert(int id, string name, string department)
    {
        root = insertNode(root, id, name, department);
    }
    void search(int id)
    {
        EmployeeNode* result = searchNode(root, id);

        if (result == NULL)
            cout << "Employee not found!\n";
        else
        {
            cout << "Employee Found!\n";
            cout << "ID: " << result->id << endl;
            cout << "Name: " << result->name << endl;
            cout << "Department: " << result->department << endl;
        }
    }

    void deleteNode(int id)
    {
        if (root == NULL)
        {
            cout << "Tree is empty!\n";
            return;
        }

        if (searchNode(root, id) == NULL)
        {
            cout << "Employee ID does not exist!\n";
            return;
        }

        root = deleteHelper(root, id);

        cout << "Employee deleted successfully!\n";
    }

    void inOrderTraversal()
    {
        if (root == NULL)
        {
            cout << "Tree is empty!\n";
            return;
        }

        inorder(root);
    }

    void findMin()
    {
        EmployeeNode* temp = minimum(root);

        if (temp == NULL)
        {
            cout << "Tree is empty!\n";
            return;
        }

        cout << "Minimum ID: " << temp->id << endl;
        cout << "Name: " << temp->name << endl;
        cout << "Department: " << temp->department << endl;
    }

    void findMax()
    {
        EmployeeNode* temp = maximum(root);

        if (temp == NULL)
        {
            cout << "Tree is empty!\n";
            return;
        }

        cout << "Maximum ID: " << temp->id << endl;
        cout << "Name: " << temp->name << endl;
        cout << "Department: " << temp->department << endl;
    }
};

int main()
{
    EmployeeBST bst;

    bst.insert(50, "Ali", "IT");
    bst.insert(30, "Ahmed", "HR");
    bst.insert(70, "Sara", "Finance");
    bst.insert(20, "Usman", "IT");
    bst.insert(40, "Ayesha", "Marketing");
    bst.insert(60, "Hassan", "HR");
    bst.insert(80, "Zain", "Finance");

    cout << "\n--- All Employees ---\n";
    bst.inOrderTraversal();

    cout << "\n--- Search Employee ---\n";
    bst.search(40);

    cout << "\n--- Minimum Employee ---\n";
    bst.findMin();

    cout << "\n--- Maximum Employee ---\n";
    bst.findMax();

    cout << "\n--- Delete Employee ---\n";
    bst.deleteNode(30);

    cout << "\n--- Updated Employee Records ---\n";
    bst.inOrderTraversal();

    return 0;
}
