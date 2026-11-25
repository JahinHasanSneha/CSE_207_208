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

    parent.resize(V);
    Rank.assign(V, 0);

    for (int i = 0; i < V; i++)
        parent[i] = i;

    long long mstCost = 0;
    int edgesUsed = 0;

    for (auto &e : edges)
    {
        int w = e[0];
        int u = e[1];
        int v = e[2];

        // if (u < 0 || u >= V || v < 0 || v >= V)
        // {
        //     cout << "Error: Invalid vertex index.\n";
        //     return -1;
        // }

        if (findParent(u) != findParent(v))
        {
            mstCost += w;
            unionSet(u, v);
            edgesUsed++;

            if (edgesUsed == V - 1)
                break;
        }
    }

    if (edgesUsed != V - 1)
    {
        cout << "Graph is disconnected. MST does not exist.\n";
        return -1;
    }

    return mstCost;
}
int main()
{
    int V, E;
    cin >> V >> E;

    vector<vector<int>> edges;

    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        // Store as {weight, u, v}
        edges.push_back({w, u, v});
    }

    long long mstCost = kruskal(V, edges);

    if (mstCost != -1)
        cout << "MST Cost: " << mstCost << endl;

    return 0;
}