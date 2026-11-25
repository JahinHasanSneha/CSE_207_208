#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> capacity_;
vector<vector<int>> origCap;   // NEW: snapshot of original capacities, taken before max-flow runs
vector<vector<int>> adj;

int bfs(int source, int sink, vector<int> &parent, int n)
{
    parent.assign(n+1, -1);
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
            if (parent[v] == -1 && capacity_[u][v] > 0)
            {
                parent[v] = u;
                int newFlow = min(flow, capacity_[u][v]);
                if (v == sink) return newFlow;
                q.push({v, newFlow});
            }
        }
    }
    return 0;
}
vector<bool> visited;

int edmondsKarp(int source, int sink, int n)
{
    int maxFlow = 0;
    vector<int> parent(n+1);
    int newFlow;
    while ((newFlow = bfs(source, sink, parent, n)))
    {
        maxFlow += newFlow;
        int cur = sink;
        while (cur != source)
        {
            int prev = parent[cur];
            capacity_[prev][cur] -= newFlow;
            capacity_[cur][prev] += newFlow;
            cur = prev;
        }
    }
    return maxFlow;
}

// FIXED: only follow an edge u->v if it was a REAL input edge (origCap[u][v] > 0)
// AND it currently carries flow (capacity_[u][v] < origCap[u][v]).
// Consuming a unit = increment capacity_[u][v] (give capacity back = remove it from
// the reconstructable-flow pool). Restore on backtrack by decrementing again.
bool findPath(int u, int sink, vector<int> &path)
{
    path.push_back(u);
    if (u == sink) return true;
    visited[u] = true;
    for (int v : adj[u])
    {
        if (!visited[v] && origCap[u][v] > 0 && capacity_[u][v] < origCap[u][v])
        {
            capacity_[u][v]++;
            if (findPath(v, sink, path)) return true;
            capacity_[u][v]--;   // restore: this unit wasn't used on this dead-end branch
        }
    }
    path.pop_back();
    return false;
}

int main()
{
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        int n, m;
        cin >> n >> m;
        capacity_.assign(n + 1, vector<int>(n + 1, 0));
        adj.assign(n + 1, vector<int>());
        for (int j = 0; j < m; j++)
        {
            int u, v;
            cin >> u >> v;
            capacity_[u][v] += 1;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        origCap = capacity_;   // snapshot BEFORE running max-flow

        int maxFlow = edmondsKarp(1, n, n);
        cout << "Case " << i << ": " << maxFlow << endl;
        if (maxFlow == 0)
        {
            cout << "No escape route possible! The Professor needs a new plan." << endl;
        }
        else
        {
            int remaining = maxFlow;
            while (remaining--)
            {
                visited.assign(n + 1, false);
                vector<int> path;
                bool ok = findPath(1, n, path);
                if (!ok) { cout << "[ERROR: findPath failed]" << endl; continue; }
                for (size_t k = 0; k < path.size(); k++)
                {
                    cout << path[k];
                    if (k != path.size() - 1) cout << " -> ";
                }
                cout << endl;
            }
        }
        cout << endl;
    }
}
