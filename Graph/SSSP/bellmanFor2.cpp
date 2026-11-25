#include <bits/stdc++.h>
using namespace std;
void bellmanFord(int src, vector<vector<pair<int, int>>> &g, int V)
{
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    for (int i = 0; i < V - 1; i++)
    {
        for (int u = 0; u < V; u++)
        {
            for (auto e : g[u])
            {
                int v = e.first;
                int wt = e.second;
                if (dist[u] != INT_MAX && dist[v] > dist[u] + wt)
                {
                    dist[v] = dist[u] + wt;
                }
            }
        }
    }
    for (int u = 0; u < V; u++)
    {
        for (auto e : g[u])
        {
            int v = e.first;
            int wt = e.second;
            if (dist[u] != INT_MAX && dist[v] > dist[u] + wt)
            {
                cout << "Negative Weight Cycle Detected!" << endl;
                return;
            }
        }
    }
    for (int i = 0; i < V; i++)
    {
        if (dist[i] == INT_MAX)
        {
            cout << "INF";
        }
        else
        {
            cout << dist[i] << " ";
        }
    }
    cout << endl;
}
int main()
{
    int V, E;
    cin >> V >> E;
    vector<vector<pair<int, int>>> g(V);
    for (int i = 0; i < E; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;
        g[u].push_back({v, wt});
        // Uncomment for an undirected graph
        // g[v].push_back({u, wt});
    }
    int src;
    cin >> src;
    bellmanFord(src, g, V);
    return 0;
}