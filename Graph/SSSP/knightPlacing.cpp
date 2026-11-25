#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main()
{

    int n, k;
    cin >> n >> k;

    vector<vector<int>> board(n, vector<int>(n));
    vector<pair<int, int>> knights;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> board[i][j];
            if (board[i][j] == 1)
                knights.push_back({i, j});
        }
    }
    // 8 knight moves
    int dx[8] = {1, 1, 2, 2, -1, -1, -2, -2};
    int dy[8] = {2, -2, 1, -1, 2, -2, 1, -1};

    // dist[idx][x][y] = shortest moves from knight idx to (x,y)
    vector<vector<vector<int>>> dist(
        knights.size(), vector<vector<int>>(n, vector<int>(n, INF)));

    for (int idx = 0; idx < (int)knights.size(); idx++)
    {
        auto [sx, sy] = knights[idx];
        queue<pair<int, int>> q;
        q.push({sx, sy});
        dist[idx][sx][sy] = 0;

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            for (int d = 0; d < 8; d++)
            {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (nx >= 0 && nx < n && ny >= 0 && ny < n &&
                    dist[idx][nx][ny] == INF)
                {
                    dist[idx][nx][ny] = dist[idx][x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }

    int ans = INF;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int total = 0;
            bool reachable = true;

            for (int idx = 0; idx < (int)knights.size(); idx++)
            {
                if (dist[idx][i][j] == INF)
                {
                    reachable = false;
                    break;
                }
                total += dist[idx][i][j];
            }

            if (reachable)
                ans = min(ans, total);
        }
    }

    cout << (ans == INF ? -1 : ans) << '\n';
    return 0;
}/*This code solves the problem by first locating all knights
 on the board, then performing a multi-source BFS from each 
 knight individually using the eight possible knight moves 
 to compute the shortest number of moves required for that 
 knight to reach every cell (storing distances in a 3D array). 
 After that, it iterates over every board cell, sums the 
 distances from all knights to that cell (only if every knight
  can actually reach it), and keeps the minimum sum as the 
  answer, outputting -1 if no cell is reachable by all knights.

*/