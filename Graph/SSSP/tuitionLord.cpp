#include <bits/stdc++.h>
using namespace std;

int main()
{
    int K;
    cin >> K;

    int N;
    cin >> N;

    int M;
    cin >> M;

    // {destination,time,cost}
    vector<vector<tuple<int,int,int>>> g(N + 1);

    for(int i = 0; i < M; i++)
    {
        int u,v,t,c;
        cin >> u >> v >> t >> c;

        g[u].push_back({v,t,c});
        g[v].push_back({u,t,c});
    }

    int src,dest;
    cin >> src >> dest;

    vector<int> dist(N + 1, INT_MAX);
    vector<int> parent(N + 1, -1);

    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    dist[src]=0;
    pq.push({0,src});

    while(!pq.empty())
    {
        auto [d,u]=pq.top();
        pq.pop();

        if(d!=dist[u])
            continue;

        for(auto [v,t,c]:g[u])
        {
            int wt;

            if(u==src)
                wt=c+K*t;
            else
                wt=c+K*t+K;

            if(dist[v]>dist[u]+wt)
            {
                dist[v]=dist[u]+wt;
                parent[v]=u;
                pq.push({dist[v],v});
            }
        }
    }

    if(dist[dest]==INT_MAX)
    {
        cout<<"ERROR";
        return 0;
    }

    vector<int> path;

    int cur=dest;

    while(cur!=-1)
    {
        path.push_back(cur);
        cur=parent[cur];
    }

    reverse(path.begin(),path.end());

    int totalTime=0;
    int travelCost=0;

    for(int i=0;i+1<path.size();i++)
    {
        int u=path[i];
        int v=path[i+1];

        for(auto [to,t,c]:g[u])
        {
            if(to==v)
            {
                totalTime+=t;
                travelCost+=c;
                break;
            }
        }
    }

    int waiting=max(0,(int)path.size()-2);
    totalTime+=waiting;

    cout<<"Path : ";

    for(int i=0;i<path.size();i++)
    {
        cout<<path[i];

        if(i+1<path.size())
            cout<<"->";
    }

    cout<<endl;

    cout<<"Total Time = "<<totalTime<<endl;

    cout<<"Total Cost = "<<travelCost+K*totalTime<<endl;

    return 0;
}