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
    int n, m, k;
    cin >> n >> m >> k;
    capacity.assign(n + m + 3, vector<int>(n + 3 + m, 0));
    adj.assign(n + m + 3, vector<int>());
    int S = n + m + 1, T = n + m + 2;
    for (int i = 1; i <= n; i++)
    {
        capacity[S][i] += 1;
        adj[S].push_back(i);
        adj[i].push_back(S);
    }
    for (int i = 0; i < k; i++)
    {
        int u, v;
        cin >> u >> v;
        v+=n;
        capacity[u][v] += 1;
        
       
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back({u, v});
    }
    for (int i = n + 1; i < n + m+1; i++)
    {
        capacity[i][T] += 1;
        adj[i].push_back(T);
        adj[T].push_back(i);
    }
    int maxFlow = edmonsKarp(S, T, n + m + 2);
    cout << maxFlow << endl;
    for (auto e : edges)
    {
        if (capacity[e.u][e.v] == 0)
        {
            cout << e.u << " " << e.v-n<< endl;
        }
    }
}