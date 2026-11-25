#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void bellmanFord(int src, vector<vector<pair<int, ll>>> &g, int V)
{
    vector<ll> dist(V + 1, LLONG_MAX);
    dist[src] = 0;
    for (int i = 1; i <= V - 1; i++)
    {
        for (int u = 1; u <= V; u++)
        {
            for (auto e : g[u])
            {
                int v = e.first;
                ll wt = e.second;
                if (dist[u] != LONG_MAX && dist[v] > dist[u] + wt)
                {
                    dist[v] = dist[u] + wt;
                }
            }
        }
    }
    for (int u = 1; u <= V; u++)
    {
        for (auto e : g[u])
        {
            int v = e.first;
            ll wt = e.second;
            if (dist[u] != LONG_MAX && dist[v] > dist[u] + wt)
            {
                cout << "Negative Weight Cycle Detected!" << endl;
                return;
            }
        }
    }

    if (dist[V] == LONG_MAX)
    {
        cout << "INF";
    }
    else
    {
        cout << -dist[V] << " ";
    }
}
int main()
{
    int V, E;
    cin >> V >> E;
    vector<vector<pair<int, ll>>> g(V + 1);
    for (int i = 1; i <= E; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;
        g[u].push_back({v, -wt});
        // Uncomment for an undirected graph
        // g[v].push_back({u, wt});
    }

    bellmanFord(1, g, V);
    return 0;
}

// So basically here we are using bellmanford algo in 
// reverse theory. What bellman does is minimizong the
//  cost while what we want is maximizing the cost, 
//  So we are negating the edge weights and adding. 
//  Finally we are also returning -dist[V] value. 
//  Why negate the weights?

// Suppose the original graph is
// 1 --5--> 2 --7--> 3
// Original score:
// 5 + 7 = 12
// Negate every edge:
// 1 ---5--> 2 ---7--> 3
// Now the path cost is
// -5 + (-7) = -12
// The path with the maximum original score 
// becomes the path with the minimum negated cost.
// So,Maximum Score=−(Minimum Negated Distance)
	