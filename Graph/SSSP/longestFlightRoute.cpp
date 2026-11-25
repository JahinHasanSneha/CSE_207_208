#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n + 1);
    vector<int> indegree(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        indegree[b]++;
    }

    // Topological Sort (Kahn's Algorithm)
    queue<int> q;

    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
            q.push(i);
    }

    vector<int> topo;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        topo.push_back(u);

        for (int v : g[u])
        {
            indegree[v]--;

            if (indegree[v] == 0)
                q.push(v);
        }
    }

    // dp[i] = maximum number of cities from 1 to i
    vector<int> dp(n + 1, INT_MIN);
    vector<int> parent(n + 1, -1);

    dp[1] = 1;

    // DP on topological order
    for (int u : topo)
    {
        if (dp[u] == INT_MIN)
            continue;

        for (int v : g[u])
        {
            if (dp[v] < dp[u] + 1)
            {
                dp[v] = dp[u] + 1;
                parent[v] = u;
            }
        }
    }

    if (dp[n] == INT_MIN)
    {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> path;

    int cur = n;
    while (cur != -1)
    {
        path.push_back(cur);
        cur = parent[cur];
    }

    reverse(path.begin(), path.end());

    cout << path.size() << endl;

    for (int x : path)
        cout << x << " ";

    cout << endl;

    return 0;
}