#include <bits/stdc++.h>
using namespace std;

vector<int> parent, Rank;

int findParent(int x)
{
    if (parent[x] == x)
        return x;
    return parent[x] = findParent(parent[x]);
}

void unionSet(int a, int b)
{
    a = findParent(a);
    b = findParent(b);

    if (a == b)
        return;

    if (Rank[a] < Rank[b])
        parent[a] = b;
    else if (Rank[a] > Rank[b])
        parent[b] = a;
    else
    {
        parent[b] = a;
        Rank[a]++;
    }
}

// Returns true if all safe cities become connected
bool kruskal(int N,
             vector<vector<int>> &edges,
             vector<bool> &risky,
             bool safeOnly,
             long long &totalCost,
             vector<pair<int, int>> &answer)
{
    for (auto &e : edges)
    {
        int w = e[0];
        int u = e[1];
        int v = e[2];

        // Ignore risky edges in Phase 1
        if (safeOnly && (risky[u] || risky[v]))
            continue;

        if (findParent(u) != findParent(v))
        {
            unionSet(u, v);
            totalCost += w;
            answer.push_back({u, v});
        }
    }

    int root = -1;

    for (int i = 0; i < N; i++)
    {
        if (!risky[i])
        {
            if (root == -1)
                root = findParent(i);
            else if (findParent(i) != root)
                return false;
        }
    }

    return true;
}

int main()
{
    int N, M, P;
    cin >> N >> M >> P;

    int K;
    cin >> K;

    vector<bool> risky(N, false);

    for (int i = 0; i < K; i++)
    {
        int x;
        cin >> x;
        risky[x] = true;
    }

    vector<vector<int>> edges;

    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        int penalty = 0;
        if (risky[u])
            penalty += P;
        if (risky[v])
            penalty += P;

        edges.push_back({w + penalty, u, v});
    }

    sort(edges.begin(), edges.end());

    parent.resize(N);
    Rank.assign(N, 0);

    for (int i = 0; i < N; i++)
        parent[i] = i;

    long long totalCost = 0;
    vector<pair<int, int>> answer;

    // Phase 1: Safe-only edges
    bool connected = kruskal(N, edges, risky, true, totalCost, answer);

    // Phase 2: Add risky edges if necessary
    if (!connected)
        kruskal(N, edges, risky, false, totalCost, answer);

    // Final check
    int root = -1;
    bool ok = true;

    for (int i = 0; i < N; i++)
    {
        if (!risky[i])
        {
            if (root == -1)
                root = findParent(i);
            else if (findParent(i) != root)
            {
                ok = false;
                break;
            }
        }
    }

    if (!ok)
    {
        cout << -1 << endl;
        return 0;
    }

    cout << answer.size() << endl;

    for (auto &e : answer)
        cout << e.first << " " << e.second << endl;

    cout << totalCost << endl;

    return 0;
}