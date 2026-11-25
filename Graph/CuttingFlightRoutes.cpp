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

vector<vector<int>> SelectedEdges;
long long kruskal(int V, vector<vector<int>> &edges)
{
    sort(edges.begin(), edges.end());

    parent.resize(V+1);
    Rank.assign(V+1, 0);

    for (int i = 1; i < V; i++)
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
            SelectedEdges.push_back({u, v, w});
            mstCost += w;
            unionSet(u, v);
            edgesUsed++;
           
            if (edgesUsed == V - 1)
                break;
        }
    }

    if (edgesUsed != V - 1)
    {
       // cout << "Graph is disconnected. MST does not exist.\n";
        return -1;
    }

    return mstCost;
}
int main()
{
    int N, M;
    cin >> N >> M;

    vector<vector<int>> edges;
    long long total = 0;
    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        total += w;
        // Store as {weight, u, v}
        edges.push_back({w, u, v});
    }

    long long mstCost = kruskal(N, edges);
    long long aSavings = total - mstCost;
    if (mstCost == -1)
        cout << "IMPOSSIBLE " << endl;
    else
    {
        cout << "Routes Shut Down. " << M-N+1 << endl;
        cout << "Total SAVINGS: " << aSavings << endl;
        cout << "Operational routes: " << endl;
        for (auto &e : SelectedEdges)
        {
            cout << e[0] << " "<<e[1]<<" "<< e[2] << endl;
        }
        return 0;
    }
}