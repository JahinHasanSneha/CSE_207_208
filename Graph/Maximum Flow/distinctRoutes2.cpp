#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> capacity;
vector<vector<int>> adj;

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
vector<bool> visited;
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
        { // Edge u->v carried one unit of flow
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
        int u, v, c;
        cin >> u >> v ;
        capacity[u][v] +=1;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int maxF = edmonsKarp(1, n, n);
    cout << maxF << endl;
    while (maxF--)
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