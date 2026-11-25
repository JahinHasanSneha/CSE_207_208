#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    vector<vector<int>> edges(n, vector<int>(n, INT_MAX));

    for (int i = 0; i < n; i++)
    {
        dist[i][i] = 0;
        edges[i][i] = 0;
    }

    for (int i = 0; i < m; i++)
    {
        int u, v, t;
        cin >> u >> v >> t;

        if (t < dist[u][v])
        {
            dist[u][v] = t;
            edges[u][v] = 1;
        }
    }

    // Floyd-Warshall
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX)
                    continue;

                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    edges[i][j] = edges[i][k] + edges[k][j];
                }
                else if (dist[i][j] == dist[i][k] + dist[k][j])
                {
                    edges[i][j] = min(edges[i][j], edges[i][k] + edges[k][j]);
                }
            }
        }
    }

    int V;
    cin >> V;

    int q;
    cin >> q;

    while (q--)
    {
        int s, d;
        cin >> s >> d;

        int ans = dist[s][d];
        int ansV = INT_MAX;

        if (dist[s][V] != INT_MAX && dist[V][d] != INT_MAX)
        {
            ansV = dist[s][V] + dist[V][d] - edges[s][V] - edges[V][d];
        }

        ans = min(ans, ansV);

        if (ans == INT_MAX)
            cout << -1 << endl;
        else
            cout << ans << endl;
    }

    return 0;
}