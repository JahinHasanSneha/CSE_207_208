#include <bits/stdc++.h>
using namespace std;

class LinearHashTable {
    static const int INIT = 13;
    int N;
    vector<string> table;
    vector<bool> tombstone; // true if slot is deleted
    int cnt;
    double maxLF = 0.7, minLF = 0.2;

    int hashFunc(const string& key) {
        int sum = 0;
        for (char c : key) sum += (unsigned char)c;
        return sum % N;
    }

    bool isPrime(int n) {
        if (n < 2) return false;
        if (n % 2 == 0) return n == 2;
        for (int d = 3; d * d <= n; d += 2)
            if (n % d == 0) return false;
        return true;
    }

    void resize(int newSize) {
        int oldN = N;
        vector<string> oldTable = table;
        vector<bool> oldTomb = tombstone;
        N = newSize;
        table.assign(N, "");
        tombstone.assign(N, false);
        cnt = 0;
        for (int i = 0; i < oldN; ++i) {
            if (!oldTable[i].empty() && !oldTomb[i]) {
                insert(oldTable[i]); // re‑insert (will also update cnt)
            }
        }
    }

    void checkResize() {
        double lf = (double)cnt / N;
        if (lf > maxLF) {
            int newN = N * 2;
            while (!isPrime(newN)) newN++;
            resize(newN);
        } else if (lf < minLF && N > INIT) {
            int newN = N / 2;
            if (newN < INIT) newN = INIT;
            while (!isPrime(newN)) newN++;
            resize(newN);
        }
    }

public:
    LinearHashTable() : N(INIT) {
        table.assign(N, "");
        tombstone.assign(N, false);
        cnt = 0;
    }

    void insert(const string& key) {
        int h = hashFunc(key);
        int i = 0;
        while (i < N) {
            int idx = (h + i) % N;
            if (table[idx].empty() || tombstone[idx]) {
                table[idx] = key;
                tombstone[idx] = false;
                cnt++;
                checkResize();
                return;
            } else if (table[idx] == key) {
                return; // duplicate
            }
            i++;
        }
    }

    bool search(const string& key) {
        int h = hashFunc(key);
        int i = 0;
        while (i < N) {
            int idx = (h + i) % N;
            if (table[idx].empty()) return false;
            if (!tombstone[idx] && table[idx] == key) return true;
            i++;
        }
        return false;
    }

    bool remove(const string& key) {
        int h = hashFunc(key);
        int i = 0;
        while (i < N) {
            int idx = (h + i) % N;
            if (table[idx].empty()) return false;
            if (!tombstone[idx] && table[idx] == key) {
                tombstone[idx] = true;
                cnt--;
                checkResize();
                return true;
            }
            i++;
        }
        return false;
    }

    void print() {
        for (int i = 0; i < N; ++i) {
            cout << i << " : ";
            if (table[i].empty()) cout << "EMPTY";
            else if (tombstone[i]) cout << "DEL";
            else cout << table[i];
            cout << "\n";
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    LinearHashTable ht;
    int n;
    cin >> n;
    string w;
    for (int i = 0; i < n; ++i) {
        cin >> w;
        ht.insert(w);
    }

    int m;
    cin >> m;
    char op;
    for (int i = 0; i < m; ++i) {
        cin >> op;
        if (op == 'I') {
            cin >> w;
            ht.insert(w);
        } else if (op == 'D') {
            cin >> w;
            ht.remove(w);
        } else if (op == 'S') {
            cin >> w;
            cout << (ht.search(w) ? "FOUND" : "NOT FOUND") << "\n";
        } else if (op == 'P') {
            ht.print();
        }
    }
    // Final print after all operations (as required)
    ht.print();

    return 0;
}