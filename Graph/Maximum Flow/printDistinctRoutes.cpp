#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> capacity;
vector<vector<int>> original;
vector<vector<int>> flow;
vector<vector<int>> adj;

int bfs(int source, int sink, vector<int> &parent, int n)
{
    parent.assign(n + 1, -1);
    parent[source] = -2;

    queue<pair<int, int>> q;
    q.push({source, INT_MAX});

    while (!q.empty())
    {
        int u = q.front().first;
        int f = q.front().second;
        q.pop();

        for (int v : adj[u])
        {
            if (parent[v] == -1 && capacity[u][v] > 0)
            {
                parent[v] = u;
                int newFlow = min(f, capacity[u][v]);

                if (v == sink)
                    return newFlow;

                q.push({v, newFlow});
            }
        }
    }

    return 0;
}

int edmondsKarp(int source, int sink, int n)
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

vector<int> path;
vector<bool> visited;

bool dfs(int u, int sink)
{
    path.push_back(u);

    if (u == sink)
        return true;

    visited[u] = true;

    for (int v : adj[u])
    {
        if (!visited[v] && flow[u][v] > 0)
        {
            if (dfs(v, sink))
                return true;
        }
    }=

    path.pop_back();
    return false;
}

int main()
{
    int n, m;
    cin >> n >> m;

    capacity.assign(n + 1, vector<int>(n + 1, 0));
    original.assign(n + 1, vector<int>(n + 1, 0));
    adj.assign(n + 1, vector<int>());
    flow.assign(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;

        capacity[u][v] += c;
        original[u][v] += c;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int maxFlow = edmondsKarp(1, n, n);

    cout << "Maximum Flow = " << maxFlow << endl;

    // Build flow graph
    for (int i = 1; i <= n; i++)
    {
        for (int v : adj[i])
        {
            if (original[i][v] > 0)
            {
                flow[i][v] = original[i][v] - capacity[i][v];
            }
        }
    }

    cout << "Distinct Routes:" << endl;

    while (true)
    {
        visited.assign(n + 1, false);
        path.clear();

        if (!dfs(1, n))
            break;

        int mn = INT_MAX;

        for (int i = 0; i + 1 < path.size(); i++)
        {
            mn = min(mn, flow[path[i]][path[i + 1]]);
        }

        for (int i = 0; i + 1 < path.size(); i++)
        {
            flow[path[i]][path[i + 1]] -= mn;
        }

        for (int i = 0; i < path.size(); i++)
        {
            cout << path[i];

            if (i != path.size() - 1)
                cout << " -> ";
        }
        cout << endl;

        //  cout << "   (flow = " << mn << ")" << endl;
    }

    return 0;
}