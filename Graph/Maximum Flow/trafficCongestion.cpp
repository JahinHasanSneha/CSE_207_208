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
struct Edge
{
    int u, v, c;
};
vector<Edge> original;
void buildGraph(int n)
{
    capacity.assign(n + 1, vector<int>(n + 1, 0));
    adj.assign(n + 1, vector<int>());
    for (auto e : original)
    {
        capacity[e.u][e.v] += e.c;
        adj[e.u].push_back(e.v);
        adj[e.v].push_back(e.u);
    }
}
int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;

        original.push_back({u, v, c});
    }
    buildGraph(n);
    int originalFlow = edmonsKarp(1, n, n);
    int P;
    cin >> P;
    vector<int> ans;
    for (int i = 1; i <= P; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        buildGraph(n);
        capacity[u][v] += c;

        adj[u].push_back(v);
        adj[v].push_back(u);
        int newFlow = edmonsKarp(1, n, n);
        if (newFlow > originalFlow)

        {
            ans.push_back(i);
        }
    }

    if (ans.empty())
        cout << "None" << endl;
    else
    {
        for (int x : ans)
        {
            cout << x << " ";
        }
    }
}