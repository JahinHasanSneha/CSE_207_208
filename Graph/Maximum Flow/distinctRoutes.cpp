#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> capacity;
vector<vector<int>> adj;
vector<bool> visited;

int dfs(int u, int t, int flow)
{
    if (u == t)
    {
        return flow;
    }
    visited[u] = true;
    for (int v : adj[u])
    {
        if (!visited[v] && capacity[u][v] > 0)
        {
            int newFlow = dfs(v, t, min(flow, capacity[u][v]));
            if (newFlow > 0)
            {
                capacity[u][v] -= newFlow;
                capacity[v][u] += newFlow;
                return newFlow;
            }
        }
    }
    return 0;
    
}
int fordFulkerson(int source, int sink, int n)
{
    int maxFlow = 0;
    while (true)
    {
        visited.assign(n + 1, false);
        int flow = dfs(source, sink, INT_MAX);
        if (flow == 0)
            break;
        maxFlow += flow;
    }
    return maxFlow;
}

bool findPath(int u, int sink, vector<int> &path)
{
    path.push_back(u);
    if (u == sink)
    {
        return true;
    }
    visited[u] = true;
    for (int v : adj[u])
    {
        if (!visited[v] && capacity[v][u] > 0)
        {
            capacity[v][u]--;
            if (findPath(v, sink, path))
            {
                return true;
            }
            capacity[v][u]++;
        }
    }
    path.pop_back();
    return false;
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
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int maxFlow = fordFulkerson(1, n, n);
    cout << maxFlow << endl;
    while (maxFlow--)
    {
        visited.assign(n + 1, false);
        vector<int> path;
        findPath(1, n, path);
        cout << path.size() << endl;
        for (int i = 0; i < path.size(); i++)
        {
            cout << path[i] << " ";
        }
        cout << endl;
    }
}