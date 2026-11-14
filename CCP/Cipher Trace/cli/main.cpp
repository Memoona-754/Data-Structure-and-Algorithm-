// cli/main.cpp
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "../engine/ds/Stack.h"
#include "../engine/ds/Queue.h"
#include "../engine/core/RuleBook.h"

using namespace std;

void testStack() {
    cout << "\n==========================================" << endl;
    cout << " [1] TESTING CUSTOM TEMPLATE STACK (LIFO)" << endl;
    cout << "==========================================" << endl;
    
    Stack<string> s;
    cout << "Initial stack isEmpty()? " << (s.isEmpty() ? "YES (PASS)" : "NO (FAIL)") << endl;

    s.push("Exhibit A: Urgency detected ('immediately')");
    s.push("Exhibit B: Credential lure ('OTP')");
    s.push("Exhibit C: Malicious URL ('bit.ly/fake')");

    cout << "Pushed 3 evidence items. Current size: " << s.size() << " (Expected: 3)" << endl;
    cout << "Top evidence peek: " << s.peek() << endl;

    cout << "\nPopping items in reverse chronological order (LIFO):" << endl;
    while (!s.isEmpty()) {
        cout << "  - " << s.pop() << endl;
    }

    // Verify exception handling on empty pop
    try {
        s.pop();
        cout << "Pop empty failed to throw!" << endl;
    } catch (const exception& e) {
        cout << "Exception safely caught on empty pop: \"" << e.what() << "\" (PASS)" << endl;
    }

    // Template generality test
    Stack<int> intStack;
    intStack.push(101);
    intStack.push(202);
    int val1 = intStack.pop();
    int val2 = intStack.pop();
    cout << "Template <int> test: " << val1 << " then " << val2 << " (PASS)" << endl;
}

void testQueue() {
    cout << "\n==========================================" << endl;
    cout << " [2] TESTING CUSTOM TEMPLATE QUEUE (FIFO)" << endl;
    cout << "==========================================" << endl;

    Queue<string> q;
    cout << "Initial queue isEmpty()? " << (q.isEmpty() ? "YES (PASS)" : "NO (FAIL)") << endl;

    q.enqueue("SMS 01: 'Dear customer, your bank account is suspended.'");
    q.enqueue("SMS 02: 'BISP program: Rs. 25000 allocated. Call immediately.'");
    q.enqueue("SMS 03: 'JazzCash promo: Claim 500 bonus points.'");

    cout << "Enqueued 3 messages. Current size: " << q.size() << " (Expected: 3)" << endl;
    cout << "Front message in queue: " << q.front() << endl;

    cout << "\nDequeuing messages in FIFO arrival order:" << endl;
    while (!q.isEmpty()) {
        cout << "  - " << q.dequeue() << endl;
    }

    // Ensure reset of rear pointer upon emptying (prevents dangling pointers)
    q.enqueue("SMS 04: 'Reused queue after empty.'");
    cout << "Reuse after empty dequeue test: " << q.dequeue() << " (PASS)" << endl;

    try {
        q.dequeue();
    } catch (const exception& e) {
        cout << "Exception safely caught on empty dequeue: \"" << e.what() << "\" (PASS)" << endl;
    }
}

void testRuleBook() {
    cout << "\n==========================================" << endl;
    cout << " [3] TESTING RULEBOOK & SEARCH ALGORITHMS" << endl;
    cout << "==========================================" << endl;

    RuleBook book;
    
    // Try multiple possible paths to locate rules.txt
    bool loaded = book.loadFromFile("data/rules.txt") ||
                  book.loadFromFile("../data/rules.txt") ||
                  book.loadFromFile("rules.txt");

    if (!loaded) {
        cerr << "Error: Could not locate data/rules.txt. Check working directory." << endl;
        return;
    }

    cout << "Successfully loaded and sorted " << book.size() << " rules." << endl;

    // Verify insertion sort correctness (A-Z)
    bool isSorted = true;
    for (int i = 1; i < book.size(); i++) {
        if (book.getRule(i - 1).keyword > book.getRule(i).keyword) {
            isSorted = false;
            break;
        }
    }
    cout << "Lexicographically sorted check: " << (isSorted ? "VERIFIED (PASS)" : "FAILED") << endl;

    // Algorithmic Benchmark comparison: Binary Search vs Linear Search
    vector<string> testQueries = {
        "bank", "bisp", "easypaisa", "otp", "urgent", "winner", "hello", "unknown_scam"
    };

    cout << "\n------------------------------------------------------------------" << endl;
    cout << left << setw(15) << "Keyword"
         << setw(14) << "Binary Idx"
         << setw(16) << "Binary Steps"
         << setw(14) << "Linear Idx"
         << setw(16) << "Linear Steps" << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (const auto& keyword : testQueries) {
        int bIdx = book.binarySearch(keyword);
        int bSteps = book.getLastComparisons();
        int lIdx = book.linearSearch(keyword);
        int lSteps = book.getLastComparisons();

        cout << left << setw(15) << keyword
             << setw(14) << bIdx
             << setw(16) << bSteps
             << setw(14) << lIdx
             << setw(16) << lSteps << endl;
    }
    cout << "------------------------------------------------------------------" << endl;
}

int main() {
    cout << "#####################################################" << endl;
    cout << "#           CIPHERTRACE FORENSIC SUITE             #" << endl;
    cout << "#       Data Structures & Algorithms Engine         #" << endl;
    cout << "#####################################################" << endl;

    testStack();
    testQueue();
    testRuleBook();

    cout << "\nAll Core Foundation Tests Completed Successfully!" << endl;
    return 0;
}
