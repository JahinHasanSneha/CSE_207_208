#include <bits/stdc++.h>
using namespace std;

void shortestPath(int src, vector<vector<int>> &g, int V)
{
    vector<int> dist(V, INT_MAX);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    while (q.size() > 0)
    {
        int u = q.front();
        q.pop();
        for (auto v : g[u])
        {
            if (dist[v] == INT_MAX)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
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
    int src;
    vector<vector<int>> g(V);
    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cin >> src;
    shortestPath(src, g, V);
}