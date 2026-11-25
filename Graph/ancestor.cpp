#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;

    // graph with 1000 nodes (though only indices 0-25 are used)
    vector<vector<int>> g(1000);

    // Read N edges, each line gives two strings.
    // Source = second character of first string, dest = first character of second.
    for (int i = 0; i < N; i++)
    {
        string s, z;
        cin >> s >> z;

        int a = s[1] - 'A';   // source index
        int b = z[0] - 'A';   // destination index

        g[a].push_back(b);    // FIX: used parentheses instead of brackets
    }

    vector<bool> vis(26, false);
    queue<pair<int, int>> q;   // (node, depth)
    q.push({0, 1});            // start from node 0 with depth 1
    vector<pair<int, int>> ans;

    while (!q.empty())
    {
        auto x = q.front();    // FIX: q.front() returns pair<int,int>, not int
        q.pop();

        if (vis[x.first])      // already visited
            continue;

        vis[x.first] = 1;      // FIX: was "vis[x.frist]" – typo

        // If current node has exactly one outgoing edge, record its neighbor
        if (g[x.first].size() == 1)   // FIX: incorrect syntax
        {
            ans.push_back({g[x.first][0], x.second + 1});
        }

        // Push all neighbors with increased depth
        for (int v : g[x.first])
        {
            q.push({v, x.second + 1});
        }
    }

    // Output results
    cout << ans.size() << endl;
    for (auto x : ans)        // FIX: x is pair<int,int>, not int
    {
        cout << (char)(x.first + 'A') << " " << x.second << endl;
    }

    return 0;
}