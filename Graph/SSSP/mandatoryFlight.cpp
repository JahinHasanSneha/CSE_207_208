
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<vector<ll>> dijkstra(int src, vector<vector<pair<int,int>>> &adj, int n)
{
    vector<vector<ll>> dist(n + 1, vector<ll>(2, LLONG_MAX));

    priority_queue<
        tuple<ll,int,int>,
        vector<tuple<ll,int,int>>,
        greater<tuple<ll,int,int>>
    > pq;

    dist[src][0] = 0;
    pq.push({0, src, 0});   // {cost,node,couponUsed}

    while (!pq.empty())
    {
        auto [d,u,used] = pq.top();
        pq.pop();

        if (d != dist[u][used])
            continue;

        for (auto [v,w] : adj[u])
        {
            // Travel without using coupon
            if (dist[v][used] > d + w)
            {
                dist[v][used] = d + w;
                pq.push({dist[v][used], v, used});
            }

            // Use coupon on this edge
            if (!used)
            {
                if (dist[v][1] > d + w/2)
                {
                    dist[v][1] = d + w/2;
                    pq.push({dist[v][1], v, 1});
                }
            }
        }
    }

    return dist;
}

int main()
{
    int n,m;
    cin>>n>>m;

    vector<vector<pair<int,int>>> adj(n+1);
    vector<vector<pair<int,int>>> rev(n+1);

    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;

        adj[u].push_back({v,w});
        rev[v].push_back({u,w});
    }

    int x,y,w;
    cin>>x>>y>>w;

    // From source
    vector<vector<ll>> dist = dijkstra(1, adj, n);

    // From destination on reversed graph
    vector<vector<ll>> revDist = dijkstra(n, rev, n);

    ll ans = LLONG_MAX;

    // Coupon used before mandatory edge
    if(dist[x][1]!=LLONG_MAX && revDist[y][0]!=LLONG_MAX)
    {
        ans = min(ans,
                  dist[x][1] + w + revDist[y][0]);
    }

    // Coupon used on mandatory edge
    if(dist[x][0]!=LLONG_MAX && revDist[y][0]!=LLONG_MAX)
    {
        ans = min(ans,
                  dist[x][0] + w/2 + revDist[y][0]);
    }

    // Coupon used after mandatory edge
    if(dist[x][0]!=LLONG_MAX && revDist[y][1]!=LLONG_MAX)
    {
        ans = min(ans,
                  dist[x][0] + w + revDist[y][1]);
    }

    if(ans==LLONG_MAX)
        cout<<"Not possible\n";
    else
        cout<<ans<<"\n";
}