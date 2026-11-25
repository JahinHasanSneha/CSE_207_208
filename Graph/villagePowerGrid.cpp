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

long long kruskal(int V, vector<vector<int>> &edges)
{
    sort(edges.begin(), edges.end());

    parent.resize(V + 1);
    Rank.assign(V + 1, 0);

    for (int i = 0; i <= V; i++)
        parent[i] = i;

    long long cost = 0;

    for (auto &e : edges)
    {
        int w = e[0];
        int u = e[1];
        int v = e[2];

        if (findParent(u) != findParent(v))
        {
            unionSet(u, v);
            cost += w;
        }
    }

    return cost;
}

int main()
{
    int N;
    cin >> N;

    vector<vector<int>> edges;

    // Power station edges
    for (int i = 1; i <= N; i++)
    {
        int p;
        cin >> p;
        edges.push_back({p, 0, i});
    }

    int M;
    cin >> M;

    // Cable edges
    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, u, v});
    }

    cout << kruskal(N, edges) << endl;

    return 0;
}