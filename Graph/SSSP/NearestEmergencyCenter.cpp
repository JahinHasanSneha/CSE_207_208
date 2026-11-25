#include <bits/stdc++.h>
using namespace std;

void dijkstra(int src, vector<vector<pair<int, int>>> &g, int V, vector<int> &dist)
{

    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});
    while (pq.size() > 0)
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d > dist[u])
        {
            continue;
        }
        for (auto e : g[u])
        {
            int v = e.first;
            int wt = e.second;
            if (dist[v] > dist[u] + wt)
            {
                dist[v] = dist[u] + wt;
                pq.push({dist[v], v});
            }
        }
    }
}
void print(int n, vector<int> &dist)
{
    for (int i = 1; i <= n; i++)
    {
        if (dist[i] == INT_MAX)
        {
            cout << -1 << endl;
        }
        else
        {
            cout << dist[i] << endl;
        }
    }
}
int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int, int>>> g(n + 1);
    vector<int> EmC(k + 1);
    for (int i = 1; i <= k; i++)
    {
        cin >> EmC[i];
    }
    for (int i = 1; i <= m; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;
        g[v].push_back({u, wt});
        // For undirected graph, also add:
        // g[v].push_back({u, wt});
    }
    vector<int> dist(n + 1, INT_MAX);
    for (int i = 1; i <= k; i++)
        dijkstra(EmC[i], g, n, dist);

    print(n, dist);
}
// int n;
// vector<long long> dist;

// int main()
// {
//     cin >> n;

//     dist.resize(n + 1, LLONG_MAX);

//     // Now dist[1...n] is valid
// }