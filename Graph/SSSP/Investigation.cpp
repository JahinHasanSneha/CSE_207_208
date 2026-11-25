#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> g(n + 1);

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
    }

    vector<long long> dist(n + 1, LLONG_MAX);
    vector<long long> ways(n + 1, 0);
    vector<int> minFlight(n + 1, INT_MAX);
    vector<int> maxFlight(n + 1, 0);

    priority_queue<pair<long long, int>,
                   vector<pair<long long, int>>,
                   greater<pair<long long, int>>>
        pq;

    dist[1] = 0;
    ways[1] = 1;
    minFlight[1] = 0;
    maxFlight[1] = 0;

    pq.push({0, 1});

    while (!pq.empty())
    {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto e : g[u])
        {
            int v = e.first;
            int w = e.second;

            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                ways[v] = ways[u];
                minFlight[v] = minFlight[u] + 1;
                maxFlight[v] = maxFlight[u] + 1;

                pq.push({dist[v], v});
            }
            else if (dist[v] == dist[u] + w)
            {
                ways[v] = (ways[v] + ways[u]);
                minFlight[v] = min(minFlight[v], minFlight[u] + 1);
                maxFlight[v] = max(maxFlight[v], maxFlight[u] + 1);
            }
        }
    }

    cout << dist[n] << " "
         << ways[n] << " "
         << minFlight[n] << " "
         << maxFlight[n] << endl;

    return 0;
}