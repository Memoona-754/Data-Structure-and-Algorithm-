
#include <iostream>
#include <vector>
using namespace std;

class DataStream {
private:
    int value;
    int k;
    vector<int> numbers;

public:
    DataStream(int v, int n) {
        value = v;
        k = n;
    }

    bool consec(int num) {
        numbers.push_back(num);

        if (numbers.size() < k) {
            return false;
        }

        for (int i = numbers.size() - k; i < numbers.size(); i++) {
            if (numbers[i] != value) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    DataStream dataStream(4, 3);

    cout << boolalpha;

    cout << dataStream.consec(4) << endl;
    cout << dataStream.consec(4) << endl;
    cout << dataStream.consec(4) << endl;
    cout << dataStream.consec(3) << endl;

    return 0;
}
