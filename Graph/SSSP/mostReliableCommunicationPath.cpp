#include <bits/stdc++.h>
#include <cfloat>
using namespace std;
using ll = long long;
void dijkstra(int src, int dest, vector<vector<pair<int, double>>> &g, int V)
{
    vector<double> dist(V + 1, 0);
    dist[src] = 1;
    priority_queue<pair<double, int>>pq;
    pq.push({1, src});
    while (pq.size() > 0)
    {
        int u = pq.top().second;
        pq.pop();
        for (auto e : g[u])
        {
            int v = e.first;
            double wt = e.second;
            if (dist[u] != DBL_MAX && dist[v] < dist[u] * wt)
            {
                dist[v] = dist[u] * wt;
                pq.push({dist[v], v});
            }
        }
    }
    if (dist[dest] == 0)
    {
        cout << -1 << endl;
    }
    else
        cout << dist[dest] << " ";
}
int main()
{
    int V, E;
    cin >> V >> E;
    vector<vector<pair<int, double>>> g(V + 1);
    int S, T;
    cin >> S >> T;
    for (int i = 1; i <= E; i++)
    {
        int u, v;
        double wt;
        cin >> u >> v >> wt;
        g[u].push_back({v, wt});
    }

    dijkstra(S, T, g, V);
    return 0;
}
