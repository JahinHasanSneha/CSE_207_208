#include <bits/stdc++.h>

using namespace std;
void dijkstra(pair<int, int> src, pair<int, int> dest, vector<vector<int>> &grid, int n, int m)
{
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    dist[src.first][src.second] = 0;
    pq.push({0, src});
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};
    while (pq.size() > 0)
    {
        int effort = pq.top().first;
        int r = pq.top().second.first;
        int c = pq.top().second.second;
        pq.pop();
        if (effort > dist[r][c])
        {
            continue;
        }

        if (r == dest.first && c == dest.second)
        {
            cout << dist[r][c] << endl;
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m)
            {
                int wt = abs(grid[r][c] - grid[nr][nc]);
                int newEffort = max(dist[r][c], wt);
                if (newEffort < dist[nr][nc])
                {
                    dist[nr][nc] = newEffort;
                    pq.push({newEffort, {nr, nc}});
                }
            }
        }
    }
    cout << -1 << endl;
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

    dijkstra({sr, sc}, {dr, dc}, grid, n, m);

    return 0;
}