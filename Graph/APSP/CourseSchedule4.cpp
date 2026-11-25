#include <bits/stdc++.h>
using namespace std;
int main()
{
    int numCourses, m;
    cin >> numCourses >> m;
    vector<vector<bool>> dist(numCourses, vector<bool>(numCourses, false));
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        dist[a][b] = true;
    }
    for (int k = 0; k < numCourses; k++)
    {
        for (int i = 0; i < numCourses; i++)
        {
            for (int j = 0; j < numCourses; j++)
            {
                if (dist[i][k] && dist[k][j])
                    dist[i][j] = true;
            }
        }
    }
    int q;
    cin >> q;

    while (q--)
    {
        int u, v;
        cin >> u >> v;

        if (dist[u][v])
            cout << "true\n";
        else
            cout << "false\n";
    }

    return 0;
}