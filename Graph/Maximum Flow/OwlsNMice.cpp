#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> capacity;
vector<vector<int>> adj;
struct Mouse
{
    double x, y;
};

struct Hole
{
    double x, y;
    int cap;
};
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
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        int M, H;
        cin >> M >> H;
        float R;
        cin >> R;
        vector<Mouse> mice(M);
        vector<Hole> holes(H);
        for (int i = 0; i < M; i++)
        {
            cin >> mice[i].x >> mice[i].y;
        }
        for (int i = 0; i < H; i++)
        {
            cin >> holes[i].x >> holes[i].y >> holes[i].cap;
        }
        capacity.assign(M + H + 2, vector<int>(M + H + 2, 0));
        adj.assign(M + H + 2, vector<int>());
        int S = M + H, T = M + H + 1;
        for (int j = 0; j < M; j++)
        {
            capacity[S][j] = 1;
            adj[S].push_back(j);
            adj[j].push_back(S);
        }
        for (int j = 0; j < M; j++)
        {
            for (int k = 0; k < H; k++)
            {
                double dx = mice[j].x - holes[k].x;
                double dy = mice[j].y - holes[k].y;
                double dist = sqrt(dx * dx + dy * dy);
                if (dist <= R)
                {
                    capacity[j][M + k] = 1;
                    adj[j].push_back(M + k);
                    adj[M + k].push_back(j);
                }
            }
        }
        for (int j = 0; j < H; j++)
        {
            capacity[M + j][T] = holes[j].cap;
            adj[M + j].push_back(T);
            adj[T].push_back(M + j);
        }
        cout<<"Case "<<i<<" "<<edmonsKarp(S,T,M+H+2)<<endl;
    }
}