#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<string> grid(n);

    queue<pair<int, int>> mq;
    pair<int, int> start;

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'M')
                mq.push({i, j});
            else if (grid[i][j] == 'A')
                start = {i, j};
        }
    }

    vector<vector<int>> monsterDist(n, vector<int>(m, INF));

    // Multi-source BFS for monsters
    while (!mq.empty()) {
        auto [x, y] = mq.front();
        mq.pop();

        if (monsterDist[x][y] != INF)
            continue;

        monsterDist[x][y] = 0;

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                continue;

            if (grid[nx][ny] == '#')
                continue;

            if (monsterDist[nx][ny] == INF) {
                monsterDist[nx][ny] = monsterDist[x][y] + 1;
                mq.push({nx, ny});
            }
        }
    }

    vector<vector<int>> dist(n, vector<int>(m, INF));
    vector<vector<pair<int, int>>> parent(
        n, vector<pair<int, int>>(m, {-1, -1}));

    vector<vector<char>> moveTaken(n, vector<char>(m));

    queue<pair<int, int>> q;

    q.push(start);
    dist[start.first][start.second] = 0;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    char dir[] = {'U', 'D', 'L', 'R'};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        // Escaped
        if (x == 0 || x == n - 1 || y == 0 || y == m - 1) {
            cout << "YES\n";

            string path;

            while (!(x == start.first && y == start.second)) {
                path += moveTaken[x][y];
                auto p = parent[x][y];
                x = p.first;
                y = p.second;
            }

            reverse(path.begin(), path.end());

            cout << path.size() << "\n";
            cout << path << "\n";
            return 0;
        }

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                continue;

            if (grid[nx][ny] == '#')
                continue;

            if (dist[nx][ny] != INF)
                continue;

            // Must arrive before the monster
            if (dist[x][y] + 1 >= monsterDist[nx][ny])
                continue;

            dist[nx][ny] = dist[x][y] + 1;
            parent[nx][ny] = {x, y};
            moveTaken[nx][ny] = dir[k];
            q.push({nx, ny});
        }
    }

    cout << "NO\n";
}