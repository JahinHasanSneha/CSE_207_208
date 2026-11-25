#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<vector<string>> equations(n, vector<string>(2));
    vector<double> values(n);

    map<string, int> mp;
    int id = 0;

    // Input equations
    for (int i = 0; i < n; i++)
    {
        cin >> equations[i][0] >> equations[i][1];
        cin >> values[i];

        if (mp.find(equations[i][0]) == mp.end())
            mp[equations[i][0]] = id++;

        if (mp.find(equations[i][1]) == mp.end())
            mp[equations[i][1]] = id++;
    }

    int m = id;

    vector<vector<double>> dist(m, vector<double>(m, -1));

    for (int i = 0; i < m; i++)
        dist[i][i] = 1.0;

    // Build graph
    for (int i = 0; i < n; i++)
    {
        int u = mp[equations[i][0]];
        int v = mp[equations[i][1]];
        double w = values[i];

        dist[u][v] = w;
        dist[v][u] = 1.0 / w;
    }

    // Floyd-Warshall
    for (int k = 0; k < m; k++)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (dist[i][k] == -1 || dist[k][j] == -1)
                    continue;

                dist[i][j] = dist[i][k] * dist[k][j];
            }
        }
    }

    int q;
    cin >> q;

    while (q--)
    {
        string s, t;
        cin >> s >> t;

        if (mp.find(s) == mp.end() || mp.find(t) == mp.end())
        {
            cout << -1.0 << endl;
            continue;
        }

        int u = mp[s];
        int v = mp[t];

        cout << dist[u][v] << endl;
    }

    return 0;
}