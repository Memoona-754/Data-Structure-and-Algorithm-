#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

class Sort {
public:
    struct Stats {
        string name;
        long long comparisons = 0;
        long long swaps = 0;
        long long total() const { return comparisons + swaps; }
    };

private:
    static Stats bubbleSort(vector<int>& a) {
        Stats s;
        s.name = "Bubble";
        int n = a.size();
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                s.comparisons++;
                if (a[j] > a[j + 1]) {
                    swap(a[j], a[j + 1]);
                    s.swaps++;
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
        return s;
    }
    static Stats selectionSort(vector<int>& a) {
        Stats s;
        s.name = "Selection";
        int n = a.size();
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                s.comparisons++;
                if (a[j] < a[minIdx]) minIdx = j;
            }
            if (minIdx != i) {
                swap(a[i], a[minIdx]);
                s.swaps++;
            }
        }
        return s;
    }
    static Stats insertionSort(vector<int>& a) {
        Stats s;
        s.name = "Insertion";
        int n = a.size();
        for (int i = 1; i < n; i++) {
            int j = i;
            while (j > 0) {
                s.comparisons++;
                if (a[j - 1] > a[j]) {
                    swap(a[j - 1], a[j]);
                    s.swaps++;
                    j--;
                } else {
                    break;
                }
            }
        }
        return s;
    }

    static string toLower(string str) {
        for (char& c : str) c = tolower((unsigned char)c);
        return str;
    }

public:
    Stats sortArray(vector<int>& arr, const string& choice) const {
        string c = toLower(choice);
        if (c == "bubble")    return bubbleSort(arr);
        if (c == "selection") return selectionSort(arr);
        if (c == "insertion") return insertionSort(arr);
        throw invalid_argument("Unknown sorting technique: " + choice);
    }
    static vector<int> randomArray(int n, int lo = 1, int hi = 1000) {
        vector<int> v(n);
        for (int& x : v) x = lo + rand() % (hi - lo + 1);
        return v;
    }
    vector<Stats> analyze(int n) const {
        vector<int> original = randomArray(n);
        vector<Stats> results;
        for (const string name : {"bubble", "selection", "insertion"}) {
            vector<int> copy = original;   // same input for a fair comparison
            results.push_back(sortArray(copy, name));
        }
        return results;
    }
};

int main() {
    srand((unsigned)time(nullptr));
    Sort sorter;

    vector<int> data = {64, 34, 25, 12, 22, 11, 90};
    string choice = "selection";
    sorter.sortArray(data, choice);
    cout << "Sorted with " << choice << " sort: ";
    for (int x : data) cout << x << " ";
    cout << "\n\n";

    int n = 100;
    vector<Sort::Stats> results = sorter.analyze(n);

    cout << "Analysis on a random array of " << n << " elements\n";
    cout << left << setw(12) << "Technique"
         << right << setw(14) << "Comparisons"
         << setw(10) << "Swaps"
         << setw(10) << "Total" << "\n";
    cout << string(46, '-') << "\n";
    for (const auto& r : results) {
        cout << left << setw(12) << r.name
             << right << setw(14) << r.comparisons
             << setw(10) << r.swaps
             << setw(10) << r.total() << "\n";
    }
    auto cmp = [](const Sort::Stats& a, const Sort::Stats& b) {
        return a.total() < b.total();
    };
    auto best  = *min_element(results.begin(), results.end(), cmp);
    auto worst = *max_element(results.begin(), results.end(), cmp);

    cout << "\nBEST  technique: " << best.name
         << " (" << best.total() << " operations)\n";
    cout << "WORST technique: " << worst.name
         << " (" << worst.total() << " operations)\n";

    return 0;
}