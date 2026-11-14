#include <iostream>
#include <string>
#include "RuleBook.h"
#include "Investigator.h"
using namespace std;
int main() {
    RuleBook book;
    book.loadFromFile("rules.txt");
    book.loadDefaults();
    Investigator det(book);
    string msg = "\"Congratulations! You have received a bonus cash reward. Claim your prize by sending CNIC to 03123456789.\"";
    ForensicVerdict v = det.analyze(msg);
    cout << "Score: " << v.cappedScore << " Raw: " << v.rawScore << endl;
    for (auto& e : v.evidenceList) {
        cout << "  " << e.found << " [" << e.weight << "] -> " << e.reason << endl;
    }
    return 0;
}
