#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m, q;
    cin >> n >> m;
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INT_MAX));
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = min(dist[a][b], c);
        dist[b][a] = min(dist[b][a], c);
    }
   
    for (int i = 1; i <= n; i++)
    {
        dist[i][i] = 0;
    }
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX)
                    continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    cin>>q;
    queue<pair<int, int>> qu;
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        qu.push({u, v});
    }
    while (qu.size() > 0)
    {
        int i = qu.front().first;
        int j = qu.front().second;
        qu.pop();
        if (dist[i][j] == INT_MAX)
            cout << -1 << endl;
        else
            cout << dist[i][j] << endl;
    }
}