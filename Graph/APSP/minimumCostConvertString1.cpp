#include <bits/stdc++.h>
using namespace std;
int main()
{
    string src, tar;
    cin >> src >> tar;
    int n;
    cin >> n;
    vector<int> cost(n);
    vector<char> changed(n);
    vector<char> original(n);
   // cout << "print ORiginal";
    for (int i = 0; i < n; i++)
    {
        cin >> original[i];
    }
   // cout << "print changed";
    for (int i = 0; i < n; i++)
    {
        cin >> changed[i];
    }
//    cout << "print cost";
    for (int i = 0; i < n; i++)
    {
        cin >> cost[i];
    }
    vector<vector<int>> dist(26, vector<int>(26, INT_MAX));
    for (int i = 0; i < n; i++)
    {
        dist[original[i] - 'a'][changed[i] - 'a'] = min(dist[original[i] - 'a'][changed[i] - 'a'], cost[i]);
    }
    for (int i = 0; i < 26; i++)
    {
        dist[i][i] = 0;
    }
    for (int k = 0; k < 26; k++)
    {
        for (int i = 0; i < 26; i++)
        {
            for (int j = 0; j < 26; j++)
            {
                if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX)
                    continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < src.size(); i++)
    {
        int u = src[i] - 'a';
        int v = tar[i] - 'a';
        if (u == v)
            continue;
        if (dist[u][v] == INT_MAX)
        {
            cout << -1;
            return 0;
        }
        ans += dist[u][v];
    }
    cout << ans << endl;
}