#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int source, int sink, vector<int> &parent, int N)
{

    parent.assign(N , -1);
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
int edmondsKarp(int source, int sink, int N)
{

    int maxFlow = 0;
    vector<int> parent(N);
    int newFlow;
    while ((newFlow = bfs(source, sink, parent, N))!=0)
    {
        maxFlow+=newFlow;
        int cur=sink;
        while(cur!=source)
        {
            int prev=parent[cur];
            capacity[prev][cur]-=newFlow;
            capacity[cur][prev]+=newFlow;
            cur=prev;
        }
    }
    return maxFlow;

}
int main()
{

    int N, M;
    cin >> N >> M;
    capacity.assign(N , vector<int>(N , 0));
    adj.assign(N, vector<int>());
    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        capacity[u][v] += w;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cout << edmondsKarp(0, N - 1, N) << endl;
    return 0;
}
