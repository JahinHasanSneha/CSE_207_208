#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void bellmanFord(vector<vector<pair<int, ll>>> &g, int V)
{
    vector<ll> dist(V + 1, 0);          // All nodes initially reachable
    vector<int> parent(V + 1, -1);

    int x = -1;

    // Bellman-Ford
    for (int i = 1; i <= V; i++)
    {
        x = -1;//Vth change mean - exists
        for (int u = 1; u <= V; u++)
        {
            for (auto e : g[u])
            {
                int v = e.first;
                ll wt = e.second;

                if (dist[v] > dist[u] + wt)
                {
                    dist[v] = dist[u] + wt;
                    parent[v] = u;
                    x = v;
                }
            }
        }
    }
    

    if (x == -1)
    {
        cout << "NO\n";
        return;
    }

    // Move inside the cycle
    for (int i = 1; i <= V; i++)
        x = parent[x];

    vector<int> cycle;
    int cur = x;

    do
    {
        cycle.push_back(cur);
        cur = parent[cur];
    } while (cur != x);

    cycle.push_back(x);
    reverse(cycle.begin(), cycle.end());

    cout << "YES\n";
    for (int node : cycle)
        cout << node << " ";
    cout << "\n";
}

int main()
{
    int V, E;
    cin >> V >> E;

    vector<vector<pair<int, ll>>> g(V + 1);

    for (int i = 0; i < E; i++)
    {
        int u, v;
        ll wt;
        cin >> u >> v >> wt;
        g[u].push_back({v, wt});
    }

    bellmanFord(g, V);

    return 0;
}