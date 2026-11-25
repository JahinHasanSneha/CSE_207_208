
#include <bits/stdc++.h>
using namespace std;
int main()
{
    string source, target;
    cin >> source >> target;
    int n;
    cin >> n;
    vector<string> original(n);
    vector<string> changed(n);
    vector<int> cost(n);
    for (int i = 0; i < n; i++)
    {
        cin >> original[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> changed[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> cost[i];
    }
    map<string, int> mp;
    int id = 0;
    for (int i = 0; i < n; i++)
    {
        if (mp.find(original[i]) == mp.end())
        {
            mp[original[i]] = id++;
        }
        if (mp.find(changed[i]) == mp.end())
            mp[changed[i]] = id++;
    }
    int m = id;
    vector<vector<int>> dist(m, vector<int>(m, INT_MAX));

    for (int i = 0; i < m; i++)
    {
        dist[i][i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        int u = mp[original[i]];
        int v = mp[changed[i]];
        dist[u][v] = min(dist[u][v], cost[i]);
    }
    for (int k = 0; k < m; k++)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX)
                {
                    continue;
                }
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    int len = source.size();
    vector<int> dp(len + 1, INT_MAX);
    dp[len] = 0;
    ;
    for (int i = len - 1; i >= 0; i--)
    {
        if (source[i] == target[i])
            dp[i] = dp[i + 1];
        for (int j = i; j < len; j++)
        {
            string s = source.substr(i, j - i + 1);
            string t = target.substr(i, j - i + 1);
            if (mp.find(s) == mp.end())
            {
                continue;
            }
            if (mp.find(t) == mp.end())
            {
                continue;
            }
            int u = mp[s];
            int v = mp[t];
            if (dist[u][v] == INT_MAX)
            {
                continue;
            }
            if (dp[j + 1] == INT_MAX)
                continue;

            dp[i] = min(dp[i], dp[j + 1] + dist[u][v]);
        }
    }
    if (dp[0] == INT_MAX)
    {
        cout << -1;
    }
    else
    {
        cout << dp[0];
    }
}
