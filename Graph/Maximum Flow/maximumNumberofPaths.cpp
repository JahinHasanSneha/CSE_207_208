#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
vector<vector<int>> capacity;

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
int fordFulkerson(int source, int sink, int N)
{
    int maxFlow = 0;
    while (true)
    {
        visited.assign(N, false);
        int flow = dfs(source, sink, INT_MAX);
        if (flow == 0)
        {
            break;
        }
        maxFlow += flow;
    }
    if(maxFlow==0)
    {
        return -1;
    }
    return maxFlow;

}
int main()
{
    int N, M;
    cin >> N >> M;
    int s, t;
    cin >> s >> t;
    capacity.assign(N, vector<int>(N, 0));
    adj.assign(N, vector<int>());
    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        capacity[u][v] += 1;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cout << fordFulkerson(s, t, N);
}