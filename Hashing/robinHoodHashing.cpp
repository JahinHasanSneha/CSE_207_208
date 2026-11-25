#include <bits/stdc++.h>
using namespace std;

class RobinHoodHash {
    static const int N = 13;
    vector<string> keys;
    vector<int> dist;
    vector<bool> occ;

    int hashFunc(const string& key) {
        int sum = 0;
        for (char c : key) sum += (unsigned char)c;
        return sum % N;
    }

public:
    RobinHoodHash() {
        keys.assign(N, "");
        dist.assign(N, 0);
        occ.assign(N, false);
    }

    bool search(const string& key) {
        int h = hashFunc(key);
        int d = 0;
        while (d < N) {
            int idx = (h + d) % N;
            if (!occ[idx]) return false;
            if (keys[idx] == key) return true;
            d++;
        }
        return false;
    }

    void insert(const string& key) {
        if (search(key)) return;

        int h = hashFunc(key);
        string curKey = key;
        int curDist = 0;

        while (true) {
            int idx = (h + curDist) % N;
            if (!occ[idx]) {
                keys[idx] = curKey;
                dist[idx] = curDist;
                occ[idx] = true;
                return;
            }
            if (curDist > dist[idx]) {
                swap(curKey, keys[idx]);
                swap(curDist, dist[idx]);
            }
            curDist++;
        }
    }

    void print() {
        for (int i = 0; i < N; ++i) {
            if (!occ[i]) cout << i << " : EMPTY\n";
            else cout << i << " : " << keys[i] << " (distance " << dist[i] << ")\n";
        }
    }
};

int main() {
    int n;
    cin >> n;
    RobinHoodHash ht;
    string w;
    for (int i = 0; i < n; ++i) {
        cin >> w;
        ht.insert(w);
    }
    ht.print();
    return 0;
}