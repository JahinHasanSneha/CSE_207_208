#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
using namespace std;

int main() {
    int nA, nB;
    cin >> nA;
    unordered_set<string> setA, setB;
    string word;

    for (int i = 0; i < nA; ++i) {
        cin >> word;
        setA.insert(word);
    }

    cin >> nB;
    for (int i = 0; i < nB; ++i) {
        cin >> word;
        setB.insert(word);
    }

    // Intersection
    cout << "Intersection: ";
    bool first = true;
    for (const string& s : setA)
        if (setB.count(s)) {
            if (!first) cout << " ";
            cout << s;
            first = false;
        }
    cout << "\n";

    // Union
    cout << "Union: ";
    first = true;
    unordered_set<string> uni = setA;
    for (const string& s : setB) uni.insert(s);
    for (const string& s : uni) {
        if (!first) cout << " ";
        cout << s;
        first = false;
    }
    cout << "\n";

    // Difference (A-B)
    cout << "Diff (A-B): ";
    first = true;
    for (const string& s : setA)
        if (!setB.count(s)) {
            if (!first) cout << " ";
            cout << s;
            first = false;
        }
    cout << "\n";

    return 0;
}