#include <bits/stdc++.h>
using namespace std;

// ---------- Your DSU (unchanged) ----------
vector<int> parent, Rank;

int findParent(int x) {
    if (parent[x] == x)
        return x;
    return parent[x] = findParent(parent[x]);
}

void unionSet(int a, int b) {
    a = findParent(a);
    b = findParent(b);

    if (a == b)
        return;

    if (Rank[a] < Rank[b])
        parent[a] = b;
    else if (Rank[a] > Rank[b])
        parent[b] = a;
    else {
        parent[b] = a;
        Rank[a]++;
    }
}

// ---------- Solution function ----------
int makeConnected(int n, vector<vector<int>>& connections) {
    // If not enough cables, impossible
    if (connections.size() < n - 1)
        return -1;

    // Initialize DSU
    parent.resize(n);
    Rank.assign(n, 0);
    for (int i = 0; i < n; ++i)
        parent[i] = i;

    // Union all edges
    for (auto& edge : connections) {
        unionSet(edge[0], edge[1]);
    }

    // Count connected components
    int components = 0;
    for (int i = 0; i < n; ++i) {
        if (findParent(i) == i)
            components++;
    }

    // Need (components - 1) operations
    return components - 1;
}

// ---------- Main (for testing) ----------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;   // number of computers, number of connections

    vector<vector<int>> connections(m, vector<int>(2));
    for (int i = 0; i < m; ++i) {
        cin >> connections[i][0] >> connections[i][1];
    }

    cout << makeConnected(n, connections) << '\n';

    return 0;
}