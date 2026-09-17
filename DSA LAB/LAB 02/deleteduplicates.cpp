#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* curr = head;

        while (curr != nullptr && curr->next != nullptr) {
            if (curr->val == curr->next->val) {
                ListNode* duplicate = curr->next;
                curr->next = curr->next->next;
                delete duplicate;
            } else {
                curr = curr->next;
            }
        }

        return head;
    }
};

ListNode* buildList(int arr[], int n) {
    if (n == 0) return nullptr;
    ListNode* head = new ListNode(arr[0]);
    ListNode* curr = head;
    for (int i = 1; i < n; i++) {
        curr->next = new ListNode(arr[i]);
        curr = curr->next;
    }
    return head;
}

void printList(ListNode* head) {
    cout << "[";
    while (head != nullptr) {
        cout << head->val;
        if (head->next != nullptr) cout << ",";
        head = head->next;
    }
    cout << "]" << endl;
}

int main() {
    int arr[] = {1, 1, 2, 3, 3};

    ListNode* head = buildList(arr, 5);

    cout << "input:  ";
    printList(head);

    Solution sol;
    head = sol.deleteDuplicates(head);

    cout << "output: ";
    printList(head);

    return 0;
}