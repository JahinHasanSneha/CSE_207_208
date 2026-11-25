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
        visited.assign(n , false);
        int flow = dfs(source, sink, INT_MAX);
        if (flow == 0)
            break;
        maxFlow += flow;
    }
    return maxFlow;
}
int main()
{
    int P, C, M;
    cin>>P>>C;
    vector<int> supply_capacity_of_plants(P);
    vector<int> demand_capacity_of_cities(C);
    for (int i = 0; i < P; i++)
    {
        cin >> supply_capacity_of_plants[i];
    }
    for (int i = 0; i < C; i++)
    {
        cin >> demand_capacity_of_cities[i];
    }
    cin >> M;
    capacity.assign(P + C + 2, vector<int>(P + C + 2, 0));
    adj.assign(P + C + 2, vector<int>());

    for (int i = 0; i < M; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        capacity[u][v] += c;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int S = P+C, T = P + C+1;
    for (int i = 0; i < P; i++)
    {
        capacity[S][i] += supply_capacity_of_plants[i];
        adj[S].push_back(i);
        adj[i].push_back(S);
    }
    for (int i = P; i < P+C; i++)
    {
        capacity[i][T] += demand_capacity_of_cities[i-P];
        adj[i].push_back(T);
        adj[T].push_back(i);
    }
    cout << fordFulkerson(S, T, P + C + 2);
}