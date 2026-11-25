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
    parent.assign(n, -1);
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
    vector<int> parent(n );
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
    int N, K, M;
    cin >> N >> K >> M;
    int S = N;
    int T = N + 1;
    capacity.assign(N+2, vector<int>(N + 2, 0));
    adj.assign(N + 2, vector<int>());
    for (int i = 0; i < K; i++)
    {
        capacity[S][i] = 1;
        adj[S].push_back(i);
        adj[i].push_back(S);
    }
    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        capacity[u][v] += 1;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back({u, v});
    }
    for (int i = K; i < N; i++)
    {
        capacity[i][T] = 1;
        adj[i].push_back(T);
        adj[T].push_back(i);
    }

    int maxMatching = edmondsKarp(S, T, N + 2);
    cout << maxMatching << endl;

    for (auto e : edges)
    {
        if (capacity[e.u][e.v] == 0)
        {
            cout << e.u << " " << e.v << endl;
        }
    }
    return 0;
}