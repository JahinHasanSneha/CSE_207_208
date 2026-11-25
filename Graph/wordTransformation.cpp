#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
using namespace std;
bool isFine(string s1, string s2)
{
    int count = 0;
    for (int i = 0; i < s1.size(); i++)
    {

        if (s1[i] != s2[i])
        {
            count++;
        }
    }

    return count == 1;
}
int bfs(int start, int tar, vector<vector<int>> &mat)
{
    queue<int> q;
    int n = mat.size();
    vector<int> dist(n, -1);
    q.push(start);
    dist[start] = 0;

    while (q.size() > 0)
    {
        int u = q.front();
        q.pop();
        if (u == tar)
        {
            return dist[u];
        }
        for (int v = 0; v < n; v++)
        {
            if (mat[u][v] == 1 && dist[v] == -1)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    return -1;
}
int getIndex(vector<string> &s, string tar)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == tar)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    int n;
    cin >> n;
    cin.ignore();
    vector<string> s;
    for (int i = 0; i < n; i++)
    {

        string temp;
        cin >> temp;
        s.push_back(temp);
    }
    string start, tar;
    cin >> start >> tar;
    vector<vector<int>> adj(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (isFine(s[i], s[j]))
            {
                adj[i][j] = 1;
                adj[j][i] = 1;
            }
        }
    }
    int startI = getIndex(s, start);
    int tarI = getIndex(s, tar);
    int ans = bfs(startI, tarI, adj);
    cout << ans << endl;
}