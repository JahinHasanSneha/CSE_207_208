#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;

        cin >> a >> b >> c;
        g[a].push_back({b, c});

    }
    vector<vector<int>>dist(n+1);//auto storage for k ways visit
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    pq.push({0,1});
    while(pq.size()>0)
    {
        auto [d,u]=pq.top();
        pq.pop();
        if(dist[u].size()>=k)
        {
            continue;

        }
        dist[u].push_back(d);
        for(auto [v,w]:g[u])
        {pq.push({d+w,v});

        }
    }
    for(int x:dist[n])
    {
        cout<<x<<" ";
    }
}