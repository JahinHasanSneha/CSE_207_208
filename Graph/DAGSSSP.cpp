#include <bits/stdc++.h>
using namespace std;
void topoSort(int u, vector<vector<pair<int, int>>> &g, vector<bool> &vis, stack<int> &st)
{
    vis[u] = true;
    for (auto e : g[u])
    {
        int v = e.first;
        if (!vis[v])
        {
            topoSort(v, g, vis, st);
        }
    }
    st.push(u);
}
void shortestPath(int src, vector<vector<pair<int, int>>> &g, int V)
{
    vector<bool> vis(V, false);
    stack<int> st;
    for (int i = 0; i < V; i++)
    {
        if (!vis[i])
        {
            topoSort(i, g, vis, st);
        }
    }
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    while (st.size() > 0)
    {
        int u = st.top();
        st.pop();
        if (dist[u] != INT_MAX)
        {
            for (auto e : g[u])
            {
                int v = e.first;
                int wt = e.second;
                if (dist[v] > dist[u] + wt)

                {
                    dist[v] = wt + dist[u];
                }
            }
        }
    }
    for (int i = 0; i < V; i++)
    {
        if (dist[i] == INT_MAX)
            cout << "INF";
        else
        {
            cout << dist[i] << " ";
        }
    }
    cout << endl;
}

int main()
{
    int V, E;
    cin >> V >> E;
    int src;
    vector<vector<pair<int, int>>> g(V);
    for (int i = 0; i < E; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;
        g[u].push_back({v, wt});
    }
    cin >> src;
    shortestPath(src, g, V);
}