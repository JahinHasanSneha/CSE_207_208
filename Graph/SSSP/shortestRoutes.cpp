#include<bits/stdc++.h>
using namespace std;
using ll=long long;
void dijkstra(int src,vector<vector<pair<int,int>>>&g,int V)
{
    vector<ll>dist(V+1,LLONG_MAX);
    dist[src]=0;
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>pq;
    pq.push({0,src});
    while(pq.size()>0)
    {
        int u=pq.top().second;
        pq.pop();
        for(auto e:g[u])
        {
            int v=e.first;
            int wt=e.second;
            if(dist[u]!=LLONG_MAX && dist[v]>dist[u]+wt)
            {
                dist[v]=dist[u]+wt;
                pq.push({dist[v],v});
            }
        }
    }
    for(int i=1;i<V+1;i++)
    {
        if(dist[i]==LLONG_MAX)
        {
            cout<<"INF";
        }
        else
        cout<<dist[i]<<" ";
    }
    cout<<endl;
}
int main()
{int V,E;
cin>>V>>E;
vector<vector<pair<int,int>>>g(V+1);
for(int i=0;i<E;i++)
{
    int u,v,wt;
    cin>>u>>v>>wt;
    g[u].push_back({v,wt});

}

dijkstra(1,g,V);
return 0;

}
