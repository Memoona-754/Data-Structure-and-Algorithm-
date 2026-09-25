#include <iostream>
using namespace std;

class Node {
public:
    string url;
    Node* prev;
    Node* next;

    Node(string u) {
        url = u;
        prev = NULL;
        next = NULL;
    }
};

class BrowserHistory {
private:
    Node* current;

public:
    BrowserHistory(string homepage) {
        current = new Node(homepage);
    }

    void visit(string url) {

        Node* newNode = new Node(url);

        current->next = newNode;
        newNode->prev = current;

        current = newNode;
    }
    string back(int steps) {

        while (steps > 0 && current->prev != NULL) {
            current = current->prev;
            steps--;
        }

        return current->url;
    }

    string forward(int steps) {

        while (steps > 0 && current->next != NULL) {
            current = current->next;
            steps--;
        }

        return current->url;
    }
};

int main() {

    BrowserHistory browserHistory("leetcode.com");

    browserHistory.visit("google.com");
    browserHistory.visit("facebook.com");
    browserHistory.visit("youtube.com");

    cout << browserHistory.back(1) << endl;
    cout << browserHistory.back(1) << endl;
    cout << browserHistory.forward(1) << endl;

    browserHistory.visit("linkedin.com");

    cout << browserHistory.forward(2) << endl;
    cout << browserHistory.back(2) << endl;
    cout << browserHistory.back(7) << endl;

    return 0;
}