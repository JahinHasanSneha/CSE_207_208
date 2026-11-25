#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// -------------------------------------------------------------
// Hash functions
// -------------------------------------------------------------
int primaryHash(const string& key) {
    int sum = 0;
    for (char c : key) sum += (unsigned char)c;
    return sum % 13;
}

int auxHash(const string& key) {
    int sum = 0;
    for (char c : key) sum += (unsigned char)c;
    return 1 + (sum % 12);   // N-1 = 12
}

// -------------------------------------------------------------
// Insert all words into buckets with capacity b
// -------------------------------------------------------------
void insertWords(vector<vector<string>>& buckets, const vector<string>& words, int b) {
    const int N = 13;
    for (const string& w : words) {
        int primary = primaryHash(w);
        int aux = auxHash(w);
        int idx = primary;
        int i = 0;
        while (true) {
            if ((int)buckets[idx].size() < b) {
                buckets[idx].push_back(w);
                break;
            }
            ++i;
            idx = (primary + i * aux) % N;
        }
    }
}

// -------------------------------------------------------------
// Output for b = 1
// -------------------------------------------------------------
void print_b1(const vector<vector<string>>& buckets) {
    cout << "b = 1 (equivalent to plain double hashing):\n";
    cout << "Slot ";
    for (int i = 0; i < 13; ++i) cout << i << " ";
    cout << "\n";
    for (int i = 0; i < 13; ++i) {
        if (buckets[i].empty()) cout << "— ";
        else cout << buckets[i][0] << " ";
    }
    cout << "\n";
}

// -------------------------------------------------------------
// Output for b = 2
// -------------------------------------------------------------
void print_b2(const vector<vector<string>>& buckets) {
    cout << "b = 2:\n";
    cout << "Bucket Contents (order inserted)\n";
    for (int i = 0; i < 13; ++i) {
        if (!buckets[i].empty()) {
            cout << i << " ";
            for (size_t j = 0; j < buckets[i].size(); ++j) {
                if (j > 0) cout << ", ";
                cout << buckets[i][j];
            }
            cout << "\n";
        }
    }
    // Print empty ranges (consecutive empty buckets)
    int start = -1;
    for (int i = 0; i < 13; ++i) {
        if (buckets[i].empty()) {
            if (start == -1) start = i;
        } else {
            if (start != -1) {
                if (start == i - 1) cout << start << " (empty)\n";
                else cout << start << "–" << i - 1 << " (empty)\n";
                start = -1;
            }
        }
    }
    if (start != -1) {
        if (start == 12) cout << start << " (empty)\n";
        else cout << start << "–" << 12 << " (empty)\n";
    }
}

// -------------------------------------------------------------
// Output for b = 4
// -------------------------------------------------------------
void print_b4(const vector<vector<string>>& buckets) {
    cout << "b = 4: every word fits directly in its primary bucket — no probing occurs at all with this dataset at b = 4. Final buckets: ";
    bool first = true;
    for (int i = 0; i < 13; ++i) {
        if (!buckets[i].empty()) {
            if (!first) cout << ", ";
            cout << "{" << i << " : ";
            for (size_t j = 0; j < buckets[i].size(); ++j) {
                if (j > 0) cout << ", ";
                cout << buckets[i][j];
            }
            cout << "}";
            first = false;
        }
    }
    cout << "\n";
}

// -------------------------------------------------------------
// Main
// -------------------------------------------------------------
int main() {
    vector<string> words = {
        "cat", "dog", "bat", "rat", "sun",
        "fun", "run", "top", "pot", "opt",
        "art", "tar"
    };

    for (int b : {1, 2, 4}) {
        vector<vector<string>> buckets(13);
        insertWords(buckets, words, b);
        if (b == 1) print_b1(buckets);
        else if (b == 2) print_b2(buckets);
        else if (b == 4) print_b4(buckets);
        cout << "\n";
    }

    return 0;
}