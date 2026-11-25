#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ------------------------------------------------------------
// Simple hash set for integers (chaining + dynamic resizing)
// ------------------------------------------------------------
class IntHashSet {
    struct Node {
        int key;
        Node* next;
        Node(int k) : key(k), next(nullptr) {}
    };

    vector<Node*> table;
    int numElements;
    int capacity;
    const double loadFactor = 0.75;

    // ------------------- hash function ------------------------
    int hash(int key) const {
        return (key < 0 ? -key : key) % capacity;
    }

    // ------------------- prime utilities ----------------------
    bool isPrime(int n) {
        if (n < 2) return false;
        if (n % 2 == 0) return n == 2;
        for (int i = 3; i * i <= n; i += 2)
            if (n % i == 0) return false;
        return true;
    }

    int nextPrime(int n) {
        if (n <= 2) return 2;
        while (!isPrime(n)) ++n;
        return n;
    }

    // ------------------- rehash --------------------------------
    void rehash() {
        int oldCap = capacity;
        capacity = nextPrime(capacity * 2);
        vector<Node*> oldTable = table;
        table.assign(capacity, nullptr);
        numElements = 0;

        for (int i = 0; i < oldCap; ++i) {
            Node* cur = oldTable[i];
            while (cur) {
                // re‑insert (duplicate free)
                int idx = hash(cur->key);
                Node* newNode = new Node(cur->key);
                newNode->next = table[idx];
                table[idx] = newNode;
                ++numElements;
                Node* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
        }
    }

public:
    IntHashSet(int initialCap = 101) : capacity(initialCap), numElements(0) {
        table.assign(capacity, nullptr);
    }

    ~IntHashSet() {
        for (int i = 0; i < capacity; ++i) {
            Node* cur = table[i];
            while (cur) {
                Node* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
        }
    }

    // insert if not already present
    void insert(int key) {
        if (contains(key)) return;
        int idx = hash(key);
        Node* newNode = new Node(key);
        newNode->next = table[idx];
        table[idx] = newNode;
        ++numElements;
        if ((double)numElements / capacity > loadFactor)
            rehash();
    }

    bool contains(int key) const {
        int idx = hash(key);
        Node* cur = table[idx];
        while (cur) {
            if (cur->key == key) return true;
            cur = cur->next;
        }
        return false;
    }

    // return all keys in the set (order does not matter)
    vector<int> getElements() const {
        vector<int> result;
        for (int i = 0; i < capacity; ++i) {
            Node* cur = table[i];
            while (cur) {
                result.push_back(cur->key);
                cur = cur->next;
            }
        }
        return result;
    }
};

// ------------------------------------------------------------
// Set operations (expected O(|A|+|B|))
// ------------------------------------------------------------
vector<int> intersection(const IntHashSet& A, const IntHashSet& B) {
    vector<int> res;
    for (int x : A.getElements())
        if (B.contains(x)) res.push_back(x);
    return res;
}

vector<int> unionSet(const IntHashSet& A, const IntHashSet& B) {
    vector<int> res;
    for (int x : A.getElements())
        res.push_back(x);
    for (int x : B.getElements())
        if (!A.contains(x)) res.push_back(x);
    return res;
}

vector<int> difference(const IntHashSet& A, const IntHashSet& B) {
    vector<int> res;
    for (int x : A.getElements())
        if (!B.contains(x)) res.push_back(x);
    return res;
}

// ------------------------------------------------------------
// Utility to print sorted result with a label
// ------------------------------------------------------------
void printSorted(const vector<int>& v, const string& label) {
    cout << label;
    if (v.empty()) {
        cout << "\n";
        return;
    }
    vector<int> sorted = v;
    sort(sorted.begin(), sorted.end());
    for (size_t i = 0; i < sorted.size(); ++i) {
        if (i > 0) cout << " ";
        cout << sorted[i];
    }
    cout << "\n";
}

// ------------------------------------------------------------
// Main
// ------------------------------------------------------------
int main() {
    int nA, nB;
    cin >> nA;
    IntHashSet setA;
    for (int i = 0; i < nA; ++i) {
        int x;
        cin >> x;
        setA.insert(x);
    }

    cin >> nB;
    IntHashSet setB;
    for (int i = 0; i < nB; ++i) {
        int x;
        cin >> x;
        setB.insert(x);
    }

    vector<int> inter = intersection(setA, setB);
    vector<int> uni   = unionSet(setA, setB);
    vector<int> diff  = difference(setA, setB);

    printSorted(inter, "Intersection: ");
    printSorted(uni,   "Union: ");
    printSorted(diff,  "Diff (A-B): ");

    return 0;
}