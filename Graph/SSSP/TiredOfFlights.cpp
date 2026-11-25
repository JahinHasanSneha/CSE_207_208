#include <bits/stdc++.h>
using namespace std;



int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int,int>>> g(n + 1);

    for(int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;//(destination, cost)
        g[u].push_back({v, w});
    }

    vector<int> dp0(n + 1, INT_MAX);
    //Minimum cost to reach city v without using the coupon yet.
    vector<int> dp1(n + 1, INT_MAX);
//Minimum cost to reach city v after already using the coupon.
    dp0[1] = 0;

    for(int i = 1; i <= k; i++)
    {
        vector<int> new0 = dp0;
        vector<int> new1 = dp1;

        for(int u = 1; u <= n; u++)
        {
            for(auto e : g[u])
            {
                int v = e.first;
                int w = e.second;

                // Coupon not used
                if(dp0[u] != INT_MAX)
                {
                    // Don't use coupon
                    new0[v] = min(new0[v], dp0[u] + w);

                    // Use coupon now
                    new1[v] = min(new1[v], dp0[u] + w / 2);
                }

                // Coupon already used
                if(dp1[u] != INT_MAX)
                {
                    new1[v] = min(new1[v], dp1[u] + w);
                }
            }
        }

        dp0 = new0;
        dp1 = new1;
    }

    if(dp1[n] == INT_MAX)
        cout << "Not possible\n";
    else
        cout << dp1[n] << endl;
}