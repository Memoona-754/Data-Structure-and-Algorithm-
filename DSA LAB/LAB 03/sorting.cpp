#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int value) {
        data = value;
        prev = NULL;
        next = NULL;
    }
};

// Insert at end
void insertEnd(Node*& head, int value) {

    Node* newNode = new Node(value);

    if (head == NULL) {
        head = newNode;
        return;
    }

    Node* temp = head;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

// Display list
void display(Node* head) {

    Node* temp = head;

    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;
}

// Sort in descending order
void sortDescending(Node* head) {

    Node* i = head;

    while (i != NULL) {

        Node* j = i->next;

        while (j != NULL) {

            if (i->data < j->data) {

                // Swap data
                int temp = i->data;
                i->data = j->data;
                j->data = temp;
            }

            j = j->next;
        }

        i = i->next;
    }
}

int main() {

    Node* N = NULL;

    // N from Q4
    insertEnd(N, 2);
    insertEnd(N, 4);
    insertEnd(N, 6);
    insertEnd(N, 8);
    insertEnd(N, 10);
    insertEnd(N, 1);
    insertEnd(N, 3);
    insertEnd(N, 5);
    insertEnd(N, 7);
    insertEnd(N, 9);

    cout << "Before sorting: ";
    display(N);

    sortDescending(N);

    cout << "After sorting: ";
    display(N);

    return 0;
}