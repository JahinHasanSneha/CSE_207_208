#include <bits/stdc++.h>
using namespace std;
class Graph
{
public:
    int n;
    vector<vector<int>> dist;
    Graph(int n, vector<vector<int>> &edges)
    {
        this->n = n;
        dist.resize(n, vector<int>(n, INT_MAX));
        for (int i = 0; i < n; i++)
        {
            dist[i][i] = 0;
        }
        for (int i = 0; i < edges.size(); i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];
            dist[u][v] = w;
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
    }
    void addEdge(vector<int> edge)
    {
        int u = edge[0];
        int v = edge[1];
        int w = edge[2];
        if (w >= dist[u][v])
        {
            return;
        }
        dist[u][v] = w;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][u] == INT_MAX || dist[v][j] == INT_MAX)
                {
                    continue;
                }
                dist[i][j] = min(dist[i][j], dist[i][u] + dist[v][j] + w);
            }
        }
    }
    int shortestPath(int node1, int node2)
    {
        if (dist[node1][node2] == INT_MAX)
        {
            return -1;
        }
        return dist[node1][node2];
    }
};
int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> edges;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    Graph g(n, edges);

    int q;
    cin >> q;

    while (q--)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            int u, v, w;
            cin >> u >> v >> w;

            g.addEdge({u, v, w});
        }
        else if (type == 2)
        {
            int u, v;
            cin >> u >> v;

            cout << g.shortestPath(u, v) << endl;
        }
    }

    return 0;
}