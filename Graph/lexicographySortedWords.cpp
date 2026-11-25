#include <bits/stdc++.h>
using namespace std;

int main() {
    
    int n;
    cin >> n;

    vector<string> words(n);
    for (int i = 0; i < n; i++)
        cin >> words[i];

    vector<int> adj[26];
    vector<int> indeg(26, 0);
    vector<bool> present(26, false);

    // Mark all letters that appear
    for (const string& w : words) {
        for (char c : w)
            present[c - 'A'] = true;
    }

    bool possible = true;

    for (int i = 0; i + 1 < n; i++) {
        const string& a = words[i];
        const string& b = words[i + 1];

        int len = min(a.size(), b.size());
        int p = 0;
        while (p < len && a[p] == b[p])
            p++;

        if (p == len) {
            // one is a prefix of the other
            if (a.size() > b.size()) {
                // e.g. "abc" before "ab" is invalid
                possible = false;
                break;
            }
            // otherwise no constraint (shorter first is fine)
        } else {
            int u = a[p] - 'A';
            int v = b[p] - 'A';
            adj[u].push_back(v);
            indeg[v]++;
        }
    }

    if (!possible) {
        cout << -1 << '\n';
        return 0;
    }

    // Kahn's algorithm
    queue<int> q;
    for (int i = 0; i < 26; i++) {
        if (present[i] && indeg[i] == 0)
            q.push(i);
    }

    string order;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(char('A' + u));

        for (int v : adj[u]) {
            indeg[v]--;
            if (indeg[v] == 0)
                q.push(v);
        }
    }

    // Check if all present letters were placed
    for (int i = 0; i < 26; i++) {
        if (present[i] && indeg[i] > 0) {
            possible = false;
            break;
        }
    }

    if (!possible)
        cout << -1 << '\n';
    else
        cout << order << '\n';

    return 0;
}