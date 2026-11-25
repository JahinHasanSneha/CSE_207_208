#include <bits/stdc++.h>
using namespace std;

// ---------- Your DSU functions (unchanged) ----------
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
vector<int> findRedundantConnection(vector<vector<int>> &edges)
{
    int n = edges.size();
    parent.resize(n + 1);
    Rank.assign(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        parent[i] = i;
    }
    for (auto &e : edges)
    {
        int u = e[0], v = e[1];
        if (findParent(u) == findParent(v))
        {
            return e;
        }
        unionSet(u, v);
    }
    return {};
}
int main()
{

    int n;
    cin >> n; // number of edges (nodes = n)

    vector<vector<int>> edges(n, vector<int>(2));
    for (int i = 0; i < n; ++i)
    {
        cin >> edges[i][0] >> edges[i][1];
    }

    vector<int> result = findRedundantConnection(edges);

    cout << result[0] << " " << result[1] << '\n';

    return 0;
}