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
        dist[i][i] = 1.0;

    for (int i = 0; i < m; i++)
    {
        string u, v;
        double rate;

        cin >> u >> rate >> v;

        int a = mp[u];
        int b = mp[v];

        dist[a][b] = max(dist[a][b], rate);
    }

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

    bool ok = false;

    for (int i = 0; i < n; i++)
    {
        if (dist[i][i] > 1.0)
        {
            ok = true;
            break;
        }
    }

    if (ok)
        cout << "Yes";
    else
        cout << "No";
}