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

void display(Node* head) {
    Node* temp = head;

    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;
}

Node* concatenate(Node* L, Node* M) {

    if (L == NULL)
        return M;

    if (M == NULL)
        return L;

    Node* temp = L;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = M;
    M->prev = temp;

    return L;
}

int main() {

    Node* L = NULL;
    Node* M = NULL;
    Node* N = NULL;

    insertEnd(L, 2);
    insertEnd(L, 4);
    insertEnd(L, 6);
    insertEnd(L, 8);
    insertEnd(L, 10);

    insertEnd(M, 1);
    insertEnd(M, 3);
    insertEnd(M, 5);
    insertEnd(M, 7);
    insertEnd(M, 9);

    cout << "List L: ";
    display(L);

    cout << "List M: ";
    display(M);

    N = concatenate(L, M);

    cout << "List N: ";
    display(N);

    return 0;
}