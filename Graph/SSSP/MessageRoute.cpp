#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> parent(n + 1, -1);
    vector<bool> vis(n + 1, false);
    queue<int> q;
    q.push(1);
    vis[1] = true;
    while (q.size() > 0)
    {
        int u = q.front();
        q.pop();
        for (int v : adj[u])
        {
            if (!vis[v])
            {
                q.push(v);
                parent[v] = u;
                vis[v] = true;
            }
        }
    }
    if (!vis[n])
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    vector<int> path;
    for (int i = n; i > 0;)
    {

        path.push_back(i);
        i = parent[i];
    }
    reverse(path.begin(), path.end());
    cout << path.size() << endl;
    for (int x : path)
    {
        cout << x << ' ';
    }
}