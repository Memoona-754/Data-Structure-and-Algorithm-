#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class MedianFinder {
private:
    priority_queue<int> lowerHalf;                                 // max-heap: smaller half
    priority_queue<int, vector<int>, greater<int>> upperHalf;      // min-heap: larger half

public:
    MedianFinder() {}

    void addNum(int num) {
        lowerHalf.push(num);                  // step 1: always insert into lower first
        upperHalf.push(lowerHalf.top());      // step 2: shift lower's max into upper
        lowerHalf.pop();

        if (upperHalf.size() > lowerHalf.size()) {   // step 3: rebalance
            lowerHalf.push(upperHalf.top());
            upperHalf.pop();
        }
    }

    double findMedian() {
        if (lowerHalf.size() > upperHalf.size())
            return lowerHalf.top();                          // odd total: lower has the extra one
        else
            return (lowerHalf.top() + upperHalf.top()) / 2.0; // even total: average both tops
    }
};

int main() {
    MedianFinder mf;
    mf.addNum(1);
    mf.addNum(2);
    cout << mf.findMedian() << endl;   // 1.5
    mf.addNum(3);
    cout << mf.findMedian() << endl;   // 2.0
    return 0;
}