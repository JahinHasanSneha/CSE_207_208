#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<string> currency(n);
    map<string, int> mp;

    for (int i = 0; i < n; i++)
    {
        cin >> currency[i];
        mp[currency[i]] = i;
    }

    int m;
    cin >> m;

    vector<vector<double>> dist(n, vector<double>(n, 0));

    for (int i = 0; i < n; i++)
    {
        dist[i][i] = 1.0;
    }

    for (int i = 0; i < m; i++)
    {
        string u, v;
        double w;
        cin >> u >> w >> v;

        dist[mp[u]][mp[v]] = max(dist[mp[u]][mp[v]], w);
    }

    // Floyd-Warshall
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] == 0 || dist[k][j] == 0)
                    continue;

                dist[i][j] = max(dist[i][j], dist[i][k] * dist[k][j]);
            }
        }
    }

    bool found = false;

    for (int i = 0; i < n; i++)
    {
        bool ok = false;

        for (int k = 0; k < n; k++)
        {
            if (dist[k][k] > 1.0)
            {
                if (dist[i][k] > 0 && dist[k][i] > 0)
                {
                    ok = true;
                    break;
                }
            }
        }

        if (ok)
        {
            cout << currency[i] << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "No Arbitrage";
    }
}