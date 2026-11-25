#include<bits/stdc++.h>
using namespace std;
void dijkstra(int src,vector<vector<pair<int,int>>>&g,int V)
{
    vector<int>dist(V,INT_MAX);
    dist[src]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    pq.push({0,src});
    while(pq.size()>0)
    {
        int d=pq.top().first;
        int u=pq.top().second;
        pq.pop();
        if(d>dist[u])
        {
            continue;
        }
        for(auto e:g[u])
        {
            int v=e.first;
            int wt=e.second;
            if(dist[v]>dist[u]+wt)
            {
                dist[v]=dist[u]+wt;
                pq.push({dist[v],v});

            }
        }
    }
    for(int i=0;i<V;i++)
    {
        if(dist[i]==INT_MAX)
        {
            cout<<"INF";
        }
        else{
            cout<<dist[i]<<" ";
        }
    }
    cout<<endl;

}
int main()
{
    int V,E;
    cin>>V>>E;
    vector<vector<pair<int,int>>>g(V);
    for(int i=0;i<E;i++)
    {
        int u,v,wt;
        cin>>u>>v>>wt;
        g[u].push_back({v,wt});
          // For undirected graph, also add:
        // g[v].push_back({u, wt});
    }
    int src;
    cin>>src;
    dijkstra(src,g,V);
}