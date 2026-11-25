#include <bits/stdc++.h>
using namespace std;

void cheapestFlight(int src, int dest, int k,
                    vector<vector<pair<int,int>>> &g, int V)
{
    vector<int> dist(V, INT_MAX);

    queue<pair<int,pair<int,int>>> q;
    // {stops,{node,cost}}

    dist[src] = 0;
    q.push({0,{src,0}});

    while(!q.empty())
    {
        int stops = q.front().first;
        int u = q.front().second.first;
        int cost = q.front().second.second;
        q.pop();

        if(stops > k)
            continue;

        for(auto e : g[u])
        {
            int v = e.first;
            int wt = e.second;

            if(cost + wt < dist[v] && stops <= k)
            {
                dist[v] = cost + wt;
                q.push({stops+1,{v,dist[v]}});
            }
        }
    }

    if(dist[dest] == INT_MAX)
        cout << -1 << endl;
    else
        cout << dist[dest] << endl;
}

int main()
{
    int V,E;
    cin>>V>>E;

    vector<vector<pair<int,int>>> g(V);

    for(int i=0;i<E;i++)
    {
        int u,v,wt;
        cin>>u>>v>>wt;

        g[u].push_back({v,wt});
    }

    int src,dest,k;
    cin>>src>>dest>>k;

    cheapestFlight(src,dest,k,g,V);

    return 0;
}