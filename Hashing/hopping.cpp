#include <bits/stdc++.h>
using namespace std;

class HopscotchHash {
    static const int N = 17;
    static const int H = 4;
    vector<string> table;
    vector<bool> occ;

    int hashFunc(const string& key) {
        int sum = 0;
        for (char c : key) sum = (sum * 31 + (unsigned char)c) % N;
        return sum;
    }

public:
    HopscotchHash() {
        table.assign(N, "");
        occ.assign(N, false);
    }

    bool search(const string& key) {
        int h = hashFunc(key);
        for (int off = 0; off < H; ++off) {
            int idx = (h + off) % N;
            if (occ[idx] && table[idx] == key) return true;
        }
        return false;
    }

    bool insert(const string& key) {
        if (search(key)) return true; // duplicate

        int h = hashFunc(key);

        // Try to place in empty slot within neighbourhood
        for (int off = 0; off < H; ++off) {
            int idx = (h + off) % N;
            if (!occ[idx]) {
                table[idx] = key;
                occ[idx] = true;
                return true;
            }
        }

        // No empty slot in neighbourhood → try to shift
        // Find any empty slot in the whole table
        int emptySlot = -1;
        for (int i = 0; i < N; ++i)
            if (!occ[i]) { emptySlot = i; break; }

        if (emptySlot == -1) return false; // table full

        // Bring the empty slot into the neighbourhood by hopping
        int current = emptySlot;
        while (true) {
            bool moved = false;
            for (int i = 0; i < N; ++i) {
                if (occ[i] && i != current) {
                    int h_i = hashFunc(table[i]);
                    int dist = (current - h_i + N) % N;
                    if (dist < H) {
                        // Move key from i to current
                        table[current] = table[i];
                        occ[current] = true;
                        occ[i] = false;
                        current = i;
                        moved = true;
                        break;
                    }
                }
            }
            if (!moved) break;

            // If current is now within neighbourhood of original hash, place new key
            if ((current - h + N) % N < H) {
                table[current] = key;
                occ[current] = true;
                return true;
            }
        }
        return false; // insertion failed
    }

    void print() {
        for (int i = 0; i < N; ++i) {
            if (!occ[i]) cout << i << " : EMPTY\n";
            else cout << i << " : " << table[i] << "\n";
        }
    }
};

int main() {
    int n;
    cin >> n;
    HopscotchHash ht;
    string w;
    for (int i = 0; i < n; ++i) {
        cin >> w;
        ht.insert(w);
    }
    ht.print();
    return 0;
}