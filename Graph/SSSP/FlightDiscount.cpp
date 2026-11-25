#include <bits/stdc++.h>
using namespace std;

int main()
{  int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);

    while (m--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    // dist[node][0] = coupon not used
    // dist[node][1] = coupon already used
    vector<vector<int>> dist(n + 1, vector<int>(2, INT_MAX));

    priority_queue<
        tuple<int, int, int>,
        vector<tuple<int, int, int>>,
        greater<tuple<int, int, int>>>
        pq;
    dist[1][0] = 0;
    pq.push({0, 1, 0}); //(cost, node, couponUsed)
    while (pq.size() > 0)
    {
        auto [d, u, used] = pq.top();
        pq.pop();
        if (d !=dist[u][used])
        {
            continue;
        }
        for (auto [v, w] : adj[u])
        {
            if (dist[v][used] > d + w)
            {
                dist[v][used] = d + w;
                pq.push({dist[v][used], v, used});
            }
            if (!used)
            {
                if (dist[v][1] > d + w / 2)
                {
                    dist[v][1] = d + w / 2;
                    pq.push({dist[v][1], v, 1});
                }
            }
        }
    }
    cout << dist[n][1] << endl;
}
