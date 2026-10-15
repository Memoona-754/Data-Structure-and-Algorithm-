
#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

class Call {
public:
    int callID;
    int arrivalTime;
    string customerName;
    int processingTime;
    bool completed;

    Call(int id, int time, string name, int duration) {
        callID = id;
        arrivalTime = time;
        customerName = name;
        processingTime = duration;
        completed = false;
    }
};

class CallCenter {
private:
    queue<Call> calls;
    int CSR;
    vector<bool> available;

public:
    CallCenter(int numberOfCSR) {
        CSR = numberOfCSR;
        available = vector<bool>(CSR, true);
    }

    void addCall(Call c) {
        calls.push(c);

        cout << "Call " << c.callID
             << " from " << c.customerName
             << " added to queue." << endl;
    }

    void processCalls() {
        while (!calls.empty()) {
            int csrIndex = -1;

            for (int i = 0; i < CSR; i++) {
                if (available[i]) {
                    csrIndex = i;
                    break;
                }
            }

            if (csrIndex == -1) {
                cout << "All CSRs are busy. "
                     << "Calls are waiting." << endl;
                break;
            }

            Call c = calls.front();
            calls.pop();
            available[csrIndex] = false;

            cout << "\nCSR " << csrIndex + 1
                 << " is handling Call " << c.callID
                 << " from " << c.customerName << endl;

            cout << "Processing time: "
                 << c.processingTime << " minutes" << endl;

            cout << "Call " << c.callID
                 << " completed." << endl;

            c.completed = true;

            available[csrIndex] = true;
        }
    }
};

int main() {
    CallCenter center(2);

    // Add incoming calls
    center.addCall(Call(101, 0, "Ali", 3));
    center.addCall(Call(102, 1, "Sara", 2));
    center.addCall(Call(103, 2, "Ahmed", 4));
    center.addCall(Call(104, 3, "Ayesha", 1));

    cout << "\n--- Processing Calls ---\n";
    center.processCalls();

    return 0;
}
