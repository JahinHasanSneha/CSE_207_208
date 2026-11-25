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

// ---------- Edge structure ----------
struct Edge {
    int u, v, w, id;
};

// ---------- Helper: MST weight with optional skip/force ----------
int mstWeight(int n, vector<Edge>& edges, int skip, int force) {
    parent.resize(n);
    Rank.assign(n, 0);
    for (int i = 0; i < n; ++i) parent[i] = i;

    int totalWeight = 0;
    int used = 0;

    // Force include edge (if given)
    if (force != -1) {
        const Edge& e = edges[force];
        unionSet(e.u, e.v);
        totalWeight += e.w;
        used++;
    }

    // Iterate edges sorted by weight
    for (const Edge& e : edges) {
        if (e.id == skip) continue;
        if (force != -1 && e.id == force) continue; // already included

        if (findParent(e.u) != findParent(e.v)) {
            unionSet(e.u, e.v);
            totalWeight += e.w;
            used++;
            if (used == n - 1) break;
        }
    }

    if (used != n - 1) return -1; // not a spanning tree
    return totalWeight;
}

// ---------- Main solution ----------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].id = i;
    }

    // Sort by weight for Kruskal
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    // Original MST weight
    int originalMST = mstWeight(n, edges, -1, -1);

    vector<int> critical, pseudo;

    for (int i = 0; i < m; ++i) {
        // Critical: MST weight increases or graph disconnects when edge is skipped
        int without = mstWeight(n, edges, i, -1);
        if (without == -1 || without > originalMST) {
            critical.push_back(i);
            continue;
        }

        // Pseudo-critical: can appear in some MST (force include)
        int with = mstWeight(n, edges, -1, i);
        if (with == originalMST) {
            pseudo.push_back(i);
        }
    }

    // Output
    for (int i = 0; i < (int)critical.size(); ++i) {
        if (i) cout << ' ';
        cout << critical[i];
    }
    cout << '\n';

    for (int i = 0; i < (int)pseudo.size(); ++i) {
        if (i) cout << ' ';
        cout << pseudo[i];
    }
    cout << '\n';

    return 0;
}