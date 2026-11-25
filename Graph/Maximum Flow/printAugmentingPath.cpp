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
int edmondsKarp(int source, int sink, int n)
{
    int maxFlow = 0;
    vector<int> parent(n+1);
    int newFlow;
    while ((newFlow = bfs(source, sink, parent, n)))
    {
        vector<int> path;
        int cur = sink;
        while (cur != source)
        {
            path.push_back(cur);
            cur = parent[cur];
        }
        path.push_back(source);
        reverse(path.begin(), path.end());
        cout << "Augmenting path: ";
        for (int i = 0; i < path.size(); i++)
        {
            cout << path[i];
            if (i != path.size() - 1)
            {
                cout << "->";
            }
        }
        cout << " flow= " << newFlow << endl;
        maxFlow += newFlow;
        cur = sink;
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
        int u, v, c;
        cin >> u >> v >> c;
        capacity[u][v] += c;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int source, sink;
    cin >> source >> sink;
    int maxFlow = edmondsKarp(source, sink, n);
    cout << "MAXIMUM FLOW " << maxFlow << endl;
}