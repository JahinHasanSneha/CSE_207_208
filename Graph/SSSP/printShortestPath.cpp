#include <bits/stdc++.h>
using namespace std;

void shortestPath(int src, int dest, vector<vector<pair<int, int>>> &g, int V)
{
    vector<int> dist(V, INT_MAX);
    vector<int> parent(V);
    for (int i = 0; i < V; i++)
    {
        parent[i] = i;
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (pq.size() > 0)
    {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        if (d < dist[u])
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
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[dest] == INT_MAX)
    {
        cout << "No Path\n";
        return;
    }
    cout << "Shortest Distance: " << dist[dest] << endl;
    vector<int> path;

    int node = dest;
    while (parent[node] != node)
    {
        path.push_back(node);
        node = parent[node];
    }
    path.push_back(src);

    reverse(path.begin(), path.end());

    cout << "Path: ";

    for (int x : path)
        cout << x << " ";
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
        g[v].push_back({u, wt});
    }

    int src, dest;
    cin >> src >> dest;

    shortestPath(src, dest, g, V);

    return 0;
}