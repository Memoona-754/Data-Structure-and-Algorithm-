
#include <iostream>
#include <vector>
using namespace std;

class ProductOfNumbers {
private:
    vector<int> numbers;

public:
    ProductOfNumbers() {
    }
    void add(int num) {
        numbers.push_back(num);
    }

    int getProduct(int k) {
        int product = 1;

        for (int i = numbers.size() - k; i < numbers.size(); i++) {
            product = product * numbers[i];
        }

        return product;
    }
};

int main() {
    ProductOfNumbers productOfNumbers;

    productOfNumbers.add(3);
    productOfNumbers.add(0);
    productOfNumbers.add(2);
    productOfNumbers.add(5);
    productOfNumbers.add(4);

    cout << productOfNumbers.getProduct(2) << endl; 
    cout << productOfNumbers.getProduct(3) << endl; 
    cout << productOfNumbers.getProduct(4) << endl; 

    productOfNumbers.add(8);

    cout << productOfNumbers.getProduct(2) << endl; 

    return 0;
}
