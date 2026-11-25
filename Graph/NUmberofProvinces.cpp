// #include <bits/stdc++.h>
// using namespace std;
// void dfs(int i, vector<vector<int>> &adj, vector<bool> &vis)
// {
//     vis[i] = true;
//     for (int j = 0; j < adj[i].size(); j++)
//     {
//         if (adj[i][j] == 1 && !vis[j])
//         {
//             dfs(j, adj, vis);
//         }
//     }
// }
// int findCircleNUm(vector<vector<int>> &isConnected)
// {
//     int n = isConnected.size();
//     int num = 0;
//     vector<bool> vis(n, false);
//     for (int i = 0; i < n; i++)
//     {
//         if (!vis[i])
//         {
//             dfs(i, isConnected, vis)
//                 num++;
//         }
//     }
//     return num;
// }
// int main()
// {
// }//do in union find
#include <bits/stdc++.h>
using namespace std;
vector<int> Rank, parent;
int findParent(int u)
{
    if (u == parent[u])
    {
        return u;
    }
    return parent[u] = findParent(parent[u]);
}
void UnionSet(int a, int b)
{
    int pa = findParent(a);
    int pb = findParent(pb);
    if (pa == pb)
        return;
    if (Rank[pa] > Rank[pb])
    {
        parent[pb] = pa;
    }
    else if (Rank[pa] < Rank[pb])
    {
        parent[pa] = pb;
    }
    else
    {
        parent[pb] = pa;
        Rank[pa]++;
    }
}
int findCircleNum(vector<vector<int>>&isConnected)
{int n=isConnected.size();
    parent.resize(n);
    Rank.assign(n,0);
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(isConnected[i][j]==1)
            {
              UnionSet(i,j);
            }
        }
    }
    int num=0;
    for(int i=0;i<n;i++)
    {
        if(findParent(i)==i)
        num++;
    }
    return num;


}
int main()
{
    vector<vector<int>> isConnected = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };

    cout << "Number of Provinces: " << findCircleNum(isConnected) << endl;

    return 0;
}