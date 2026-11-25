#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> capacity;
vector<vector<int>> adj;
struct Partner
{
    int ExpY;
    int age;
    int CrimR;
    int Origin;
    int weap;
    int Tru;
    int lang;
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
// }
// int ExpY;
// int age;
// int  CrimR;
// int Origin;
// int weap;
// int Tru;
// int lang;
int main()
{
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        int N, M;
        cin >> M >> N;

        vector<Partner> g(M);

        for (int i = 0; i < M; i++)
        {
            cin >> g[i].ExpY >> g[i].age >> g[i].CrimR >> g[i].Origin >> g[i].weap >> g[i].Tru >> g[i].lang;
        }
        vector<Partner> p(N);
        for (int i = 0; i < N; i++)
        {
            cin >> p[i].ExpY >> p[i].age >> p[i].CrimR >> p[i].Origin >> p[i].weap >> p[i].Tru >> p[i].lang;
        }

        capacity.assign(M + N + 2, vector<int>(M + N + 2, 0));
        adj.assign(M + N + 2, vector<int>());
        int S = M + N, T = M + N + 1;
        for (int j = 0; j < M; j++)
        {
            capacity[S][j] = 1;
            adj[S].push_back(j);
            adj[j].push_back(S);
        }
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < M; k++)
            {
                // }
                // int ExpY;
                // int age;
                // int  CrimR;
                // int Origin;
                // int weap;
                // int Tru;
                // int lang;
                if (abs(p[j].ExpY - g[k].ExpY) <= 12 &&
                    abs(p[j].age - g[k].age )<= 5 &&
                    p[j].CrimR == g[k].CrimR &&
                    p[j].Origin == g[k].Origin &&
                    max(p[j].weap, g[k].weap) == 1 &&
                    p[j].Tru + g[k].Tru >= 10 &&
                    (p[j].lang & g[k].lang) != 0)
                {
                    capacity[k][M + j] = 1;
                    adj[k].push_back(M + j);
                    adj[M + j].push_back(k);
                }
            }
        }
        for (int j = 0; j < N; j++)
        {
            capacity[M + j][T] = 1;
            adj[M + j].push_back(T);
            adj[T].push_back(M + j);
        }
        cout << "Case " << i << " " << edmonsKarp(S, T, M + N + 2) << endl;
    }
}