#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> capacity;
vector<vector<int>> adj;
struct Edge
{
    int u, v;
};
vector<Edge> edges;
int bfs(int source, int sink, vector<int> &parent, int n)
{
    parent.assign(n + 1, -1);
    parent[source] = -2;
    queue<pair<int, int>> q;
    q.push({source, INT_MAX});
    while (q.size() > 0)
    {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();
        for (int v : adj[u])
        {
            if (parent[v] == -1 && capacity[u][v] > 0)
            {
                parent[v] = u;
                int newFlow = min(flow, capacity[u][v]);
                if (v == sink)
                {
                    return newFlow;
                }
                q.push({v, newFlow});
            }
        }
    }
    return 0;
}

int edmonsKarp(int source, int sink, int n)
{
    int maxFlow = 0;
    vector<int> parent(n + 1);
    int newFlow;
    while ((newFlow = bfs(source, sink, parent, n)))
    {
        maxFlow += newFlow;
        int cur = sink;
        while (cur != source)
        {
            int prev = parent[cur];
            capacity[prev][cur] -= newFlow;
            capacity[cur][prev] += newFlow;
            cur = prev;
        }
    }
    return maxFlow;
}
int main()
{
    int n, m;
    cin >> n >> m;
    capacity.assign(n + 1, vector<int>(n + 1, 0));
    adj.assign(n + 1, vector<int>());
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        capacity[u][v] += 1;
        capacity[v][u] += 1;
        edges.push_back({u, v});
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int maxFlow = edmonsKarp(1, n, n);
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    while (q.size() > 0)
    {
        int u = q.front();
        q.pop();
        for (int v : adj[u])
        {
            if (!visited[v] && capacity[u][v] > 0)
            {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << maxFlow << endl;
    for (auto e : edges)
    {
        if (visited[e.u] && !visited[e.v])
        {
            cout << e.u << " " << e.v << endl;
        }
        else if (visited[e.v] && !visited[e.u])
        {
            cout << e.v << " " << e.u << endl;
        }
    }
}