#include <bits/stdc++.h>
using namespace std;

void dijkstra(int src, int dest, vector<vector<pair<int,int>>> &g, int V)
{
    vector<int> dist(V, INT_MAX);
    vector<int> ways(V, 0);

    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    dist[src] = 0;
    ways[src] = 1;

    pq.push({0, src});

    while(!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if(d > dist[u])
            continue;

        for(auto e : g[u])
        {
            int v = e.first;
            int wt = e.second;

            if(dist[v] > dist[u] + wt)
            {
                dist[v] = dist[u] + wt;
                ways[v] = ways[u];

                pq.push({dist[v], v});
            }
            else if(dist[v] == dist[u] + wt)
            {
                ways[v] += ways[u];
            }
        }
    }

    if(dist[dest] == INT_MAX)
    {
        cout << -1 << endl;
        return;
    }

    cout << "Shortest Distance = " << dist[dest] << endl;
    cout << "Number of Ways = " << ways[dest] << endl;
}

int main()
{
    int V, E;
    cin >> V >> E;

    vector<vector<pair<int,int>>> g(V);

    for(int i = 0; i < E; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;

        g[u].push_back({v, wt});
        g[v].push_back({u, wt});
    }

    int src, dest;
    cin >> src >> dest;

    dijkstra(src, dest, g, V);

    return 0;
}