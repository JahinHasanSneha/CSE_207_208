#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, M, F;
    cin >> N >> M >> F;

    vector<int> capacity(N + 1);

    for (int i = 1; i <= N; i++)
        cin >> capacity[i];

    vector<vector<pair<int, int>>> g(N + 1);

    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    int K;
    cin >> K;

    vector<int> dist(N + 1, INT_MAX);

    priority_queue<pair<int, int>,
                   vector<pair<int, int>>,
                   greater<pair<int, int>>> pq;

    dist[1] = 0;
    pq.push({0, 1});

    // Dijkstra
    while (!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto e : g[u])
        {
            int v = e.first;
            int wt = e.second;

            if (dist[v] > dist[u] + wt)
            {
                dist[v] = dist[u] + wt;
                pq.push({dist[v], v});
            }
        }
    }

    // {total cost, lab}
    vector<pair<int, int>> labs;

    for (int i = 1; i <= N; i++)
    {
        labs.push_back({dist[i] + F, i});
    }

    sort(labs.begin(), labs.end());

    int ptr = 0;

    for (int student = 1; student <= K; student++)
    {
        while (ptr < labs.size() && capacity[labs[ptr].second] == 0)
            ptr++;

        if (ptr == labs.size())
        {
            cout << -1;
        }
        else
        {
            cout << labs[ptr].first;

            capacity[labs[ptr].second]--;
        }

        if (student != K)
            cout << " ";
    }

    cout << endl;

    return 0;
}