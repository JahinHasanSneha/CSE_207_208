#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m, q;
    cin >> n >> m;
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
   
    for (int i = 0; i < m; i++)
    {
        int u, v, t;
        cin >> u >> v >> t;
        dist[u][v] = min(t, dist[u][v]);
    }
    int X, Y;
    cin >> X >> Y;
    for (int i = 0; i < n; i++)
    {
        dist[i][i] = 0;
    }
   
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX)
                {
                    continue;
                }
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
   
    cin>>q;
    while (q--)
    {
        int s, d;
        cin >> s >> d;
        int ansX = INT_MAX;
        int ansY = INT_MAX;
        if (dist[s][X] != INT_MAX && dist[X][d] != INT_MAX)
        {
            ansX = dist[s][X] + dist[X][d];
        }
        if (dist[s][Y] != INT_MAX && dist[Y][d] != INT_MAX)
        {
            ansY = dist[s][Y] + dist[Y][d];
        }
        if (ansX == INT_MAX && ansY == INT_MAX)
        {
            cout << -1<<endl;
        }
        else
        {
            cout << min(ansX, ansY) << endl;
        }
    }
}