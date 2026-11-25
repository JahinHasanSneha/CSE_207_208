#include <bits/stdc++.h>
using namespace std;

// ---------- Your DSU (extended) ----------
vector<int> parent, Rank, sz;
int components, largest;

int findParent(int x) {
    if (parent[x] == x)
        return x;
    return parent[x] = findParent(parent[x]);
}

// Modified unionSet to also maintain component count and max size
void unionSet(int a, int b) {
    a = findParent(a);
    b = findParent(b);

    if (a == b)
        return;

    // Union by rank
    if (Rank[a] < Rank[b])
        swap(a, b);

    parent[b] = a;

    if (Rank[a] == Rank[b])
        Rank[a]++;

    // Update component sizes
    sz[a] += sz[b];
    components--;
    largest = max(largest, sz[a]);
}

// ---------- Main ----------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    parent.resize(n + 1);
    Rank.assign(n + 1, 0);
    sz.assign(n + 1, 1);

    for (int i = 1; i <= n; ++i)
        parent[i] = i;

    components = n;
    largest = 1;   // since n >= 1

    while (m--) {
        int a, b;
        cin >> a >> b;
        unionSet(a, b);
        cout << components << ' ' << largest << '\n';
    }

    return 0;
}