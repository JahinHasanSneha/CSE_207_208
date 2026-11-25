#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    int dThres;
    cin >> dThres;

    int ans = -1;
    int mn = INT_MAX;

    for (int src = 0; src < n; src++)
    {
        vector<int> dist(n, INT_MAX);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty())
        {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u])
                continue;

            for (auto it : adj[u])
            {
                int v = it.first;
                int w = it.second;

                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        int cnt = 0;

        for (int i = 0; i < n; i++)
        {
            if (i != src && dist[i] <= dThres)
                cnt++;
        }

        if (cnt <= mn)
        {
            mn = cnt;
            ans = src;
        }
    }

    cout << ans;
}