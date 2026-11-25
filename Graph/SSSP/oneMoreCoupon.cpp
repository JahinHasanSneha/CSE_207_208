
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n + 1);

    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
    }
    priority_queue<tuple<int, int, int>,
                   vector<tuple<int, int, int>>,
                   greater<tuple<int, int, int>>>
        pq; //cost,node,used
    pq.push({0, 1, 0});
    vector<vector<int>> dist(n + 1, vector<int>(3, INT_MAX));
    dist[1][0]=0;
    while (pq.size() > 0)
    {
        auto [d, u, used] = pq.top();
        pq.pop();
        for (auto [v, w] : g[u])
        {
            if (dist[v][used] > d + w)
            {
                dist[v][used] = d + w;
                pq.push({dist[v][used], v, used});
            }
            if (used<2)
            {
                if (dist[v][used+1] > d + w / 2)
                {
                    dist[v][used+1] = d + w / 2;
                    pq.push({dist[v][used+1], v, used+1});
                }
            }
        }
    }
    cout << min({dist[n][0], dist[n][1], dist[n][2]}) << endl;
}