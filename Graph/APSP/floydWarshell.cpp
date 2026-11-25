#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INT_MAX));

    // Distance from a node to itself is 0
    for (int i = 1; i <= n; i++)
        dist[i][i] = 0;

    // Read edges
    for (int i = 0; i < m; i++)
    {
        int u, v;
        int w;
        cin >> u >> v >> w;

        // If multiple edges exist, keep the minimum weight
        dist[u][v] = min(dist[u][v], w);

        // Uncomment this for an undirected graph
        // dist[v][u] = min(dist[v][u], w);
    }

    // Floyd-Warshall Algorithm
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

    // Print shortest distance matrix
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (dist[i][j] == INT_MAX)
                cout << "INT_MAX ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 1; i <= n; i++)
    {
        if (dist[i][i] < 0)
        {
            cout << "Negative weighted cycle exists" << endl;
            return 0;
        }
    }

    return 0;
}