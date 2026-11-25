#include <bits/stdc++.h>
using namespace std;

// ------- Custom Big Integer (no external libs) -------
struct BigInt {
    static const int BASE = 1000000000;
    vector<int> dig; // least significant first

    BigInt(long long v = 0) {
        if (v == 0) { dig.push_back(0); return; }
        while (v > 0) {
            dig.push_back(v % BASE);
            v /= BASE;
        }
    }

    BigInt operator*(int x) const {
        BigInt res;
        res.dig.clear();
        long long carry = 0;
        for (int d : dig) {
            long long cur = 1LL * d * x + carry;
            res.dig.push_back(cur % BASE);
            carry = cur / BASE;
        }
        while (carry) {
            res.dig.push_back(carry % BASE);
            carry /= BASE;
        }
        while (res.dig.size() > 1 && res.dig.back() == 0) res.dig.pop_back();
        return res;
    }

    // exact division by a small int (x must divide the number)
    BigInt operator/(int x) const {
        BigInt res;
        res.dig.clear();
        long long rem = 0;
        for (int i = (int)dig.size() - 1; i >= 0; --i) {
            long long cur = rem * BASE + dig[i];
            res.dig.push_back(cur / x);
            rem = cur % x;
        }
        reverse(res.dig.begin(), res.dig.end());
        while (res.dig.size() > 1 && res.dig.back() == 0) res.dig.pop_back();
        return res;
    }

    bool operator<(const BigInt& other) const {
        if (dig.size() != other.dig.size()) return dig.size() < other.dig.size();
        for (int i = (int)dig.size() - 1; i >= 0; --i)
            if (dig[i] != other.dig[i]) return dig[i] < other.dig[i];
        return false;
    }

    bool operator>(const BigInt& other) const { return other < *this; }
    bool operator==(const BigInt& other) const { return dig == other.dig; }
    bool operator==(int x) const { return *this == BigInt(x); }

    string toString() const {
        string s = to_string(dig.back());
        for (int i = (int)dig.size() - 2; i >= 0; --i) {
            string part = to_string(dig[i]);
            s += string(9 - part.size(), '0') + part;
        }
        return s;
    }
};

// ------- DSU (unchanged from your code) -------
vector<int> parent, Rank;

int findParent(int x) {
    if (parent[x] == x) return x;
    return parent[x] = findParent(parent[x]);
}

void unionSet(int a, int b) {
    a = findParent(a);
    b = findParent(b);
    if (a == b) return;
    if (Rank[a] < Rank[b]) parent[a] = b;
    else if (Rank[a] > Rank[b]) parent[b] = a;
    else {
        parent[b] = a;
        Rank[a]++;
    }
}

struct Edge {
    int u, v, w, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<Edge> edges(M);
    for (int i = 0; i < M; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].id = i;
    }

    // Sort by weight (additive MST is same as minimum product)
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    // ---------- Build MST with Kruskal ----------
    parent.resize(N + 1);
    Rank.assign(N + 1, 0);
    for (int i = 1; i <= N; ++i) parent[i] = i;

    vector<bool> inMST(M, false);
    vector<vector<pair<int,int>>> adj(N + 1); // neighbour, edge index
    BigInt mstProduct = 1;
    int used = 0;

    for (int i = 0; i < M && used < N - 1; ++i) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if (findParent(u) != findParent(v)) {
            unionSet(u, v);
            inMST[i] = true;
            mstProduct = mstProduct * w;
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});
            ++used;
        }
    }

    if (used != N - 1) {
        cout << -1 << '\n';
        return 0;
    }

    // ---------- Find second‑best product via edge exchange ----------
    BigInt secondBest = -1; // sentinel

    for (int i = 0; i < M; ++i) {
        if (inMST[i]) continue;

        int u = edges[i].u, v = edges[i].v, w = edges[i].w;

        // BFS to find path u → v in MST and the heaviest edge on it
        vector<int> parentNode(N + 1, -1), parentEdge(N + 1, -1);
        queue<int> q;
        q.push(u);
        parentNode[u] = u;

        while (!q.empty()) {
            int cur = q.front(); q.pop();
            if (cur == v) break;
            for (auto [nxt, eid] : adj[cur]) {
                if (parentNode[nxt] == -1) {
                    parentNode[nxt] = cur;
                    parentEdge[nxt] = eid;
                    q.push(nxt);
                }
            }
        }

        int maxW = -1, maxEdgeId = -1;
        int cur = v;
        while (cur != u) {
            int eid = parentEdge[cur];
            if (edges[eid].w > maxW) {
                maxW = edges[eid].w;
                maxEdgeId = eid;
            }
            cur = parentNode[cur];
        }

        BigInt candidate = (mstProduct / maxW) * w; // exact division

        if (candidate > mstProduct) {
            if (secondBest == -1 || candidate < secondBest)
                secondBest = candidate;
        }
    }

    if (secondBest == -1)
        cout << -1 << '\n';
    else
        cout << secondBest.toString() << '\n';

    return 0;
}