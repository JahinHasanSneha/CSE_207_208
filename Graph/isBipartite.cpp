#include <bits/stdc++.h>
using namespace std;
bool isBipartiteHelper(int n, int src, vector<vector<int>> &adj, vector<bool> &visited)
{
    vector<int> color(n, -1);
    queue<int> q;
    q.push(src);
    visited[src] = true;
    color[src] = 0;
    while (q.size() > 0)
    {
        int u = q.front();
        q.pop();
        for (int v : adj[u])
        {
            if (color[v] == -1)
            {
                color[v] = 1-color[u];
                visited[v] = true;
                q.push(v);
            }
            else if (color[v] == color[u])
            {
                return false;
            }
        }
    }
    return true;
}
void isBipartite(vector<vector<int>> &adj, int n)
{
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            if (!isBipartiteHelper(n, i, adj, visited))
            {
                cout << "Not Bipartite"<<endl;
                return;
            }
        }
    }
    cout << "Bipartite"<<endl;
}
int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    isBipartite(adj, n);

    return 0;
}