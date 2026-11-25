#include<bits/stdc++.h>
using namespace std;

class Solution {
    public:
        vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
            if (n == 1) {
                return {0};
            }
            vector<vector<int>> adj(n);
            vector<int> degree(n, 0);
            for (auto& e : edges) {
                int u = e[0];
                int v = e[1];
                adj[u].push_back(v);
                adj[v].push_back(u);
                degree[u]++;
                degree[v]++;
            }
            queue<int> q;
            for (int i = 0; i < n; i++) {
                if (degree[i] == 1) {
                    q.push(i);
                }
            }
            // int remain = n;
            // while (remain > 2) {
                int sz = q.size();
               // remain-=sz;
                while(sz--)
                {
                    int y=q.front();
                    q.pop();
                    for(int x:adj[y])
                    {
                        degree[x]--;
                        if(degree[x]==1)
                        {
                            q.push(x);
                        }
                    }
                }
           // }
            vector<int>ans;
            while(q.size()>0)
            {
                ans.push_back(q.front());
                q.pop();
        }
        return ans;}
    };