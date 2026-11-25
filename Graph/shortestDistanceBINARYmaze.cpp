#include <bits/stdc++.h>
using namespace std;

int shortestPath(vector<vector<int>> &grid, pair<int, int> src,
                 pair<int, int> dest, int n, int m)
{
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));

    queue<pair<int, int>> q;

    dist[src.first][src.second] = 0;
    q.push(src);

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    while (!q.empty())
    {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        if (r == dest.first && c == dest.second)
            return dist[r][c];

        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < n &&
                nc >= 0 && nc < m &&
                grid[nr][nc] == 1 &&
                dist[nr][nc] == INT_MAX)
            {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    return -1;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }

    int sr, sc, dr, dc;
    cin >> sr >> sc >> dr >> dc;

    cout << shortestPath(grid, {sr, sc}, {dr, dc}, n, m);

    return 0;
}