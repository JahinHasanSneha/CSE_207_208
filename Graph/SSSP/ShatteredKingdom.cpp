#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void bellmanFord(vector<vector<pair<int,int>>> &g,
                 vector<bool> &blocked,
                 vector<int> &capital,
                 vector<int> &query,
                 int V)
{
    vector<ll> dist(V + 1, LLONG_MAX);

    // Super Source = 0
    dist[0] = 0;

    // Bellman-Ford
    for (int i = 0; i < V; i++)
    {
        bool changed = false;

        // Edges from super source
        for (int src : capital)
        {
            if (blocked[src])
                continue;

            if (dist[src] > 0)
            {
                dist[src] = 0;
                changed = true;
            }
        }

        // Relax all graph edges
        for (int u = 1; u <= V; u++)
        {
            if (blocked[u])
                continue;

            if (dist[u] == LLONG_MAX)
                continue;

            for (auto e : g[u])
            {
                int v = e.first;
                int wt = e.second;

                if (blocked[v])
                    continue;

                if (dist[v] > dist[u] + wt)
                {
                    dist[v] = dist[u] + wt;
                    changed = true;
                }
            }
        }

        if (!changed)
            break;
    }

    // Negative cycle detection
    for (int u = 1; u <= V; u++)
    {
        if (blocked[u])
            continue;

        if (dist[u] == LLONG_MAX)
            continue;

        for (auto e : g[u])
        {
            int v = e.first;
            int wt = e.second;

            if (blocked[v])
                continue;

            if (dist[v] > dist[u] + wt)
            {
                cout << "Abyss Detected\n";
                return;
            }
        }
    }

    // Print answers
    for (int x : query)
    {
        if (blocked[x] || dist[x] == LLONG_MAX)
            cout << "INF\n";
        else
            cout << dist[x] << "\n";
    }
}

int main()
{
    int V, E, K, B, Q;
    cin >> V >> E >> K >> B >> Q;

    vector<int> capital(K);
    for (int i = 0; i < K; i++)
        cin >> capital[i];

    vector<bool> blocked(V + 1, false);

    for (int i = 0; i < B; i++)
    {
        int x;
        cin >> x;
        blocked[x] = true;
    }

    vector<int> query(Q);
    for (int i = 0; i < Q; i++)
        cin >> query[i];

    vector<vector<pair<int,int>>> g(V + 1);

    for (int i = 0; i < E; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;

        if (blocked[u] || blocked[v])
            continue;

        g[u].push_back({v, wt});
    }

    bellmanFord(g, blocked, capital, query, V);

    return 0;
}