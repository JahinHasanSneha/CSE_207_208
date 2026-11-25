#include <bits/stdc++.h>
using namespace std;
int main()
{
    int stx=-1, sty=-1;
    int W, H;
    cin >> W >> H;
    vector<vector<char>> grid(H, vector<char>(W));
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            char temp;
            cin >> temp;
            grid[i][j] = temp; 
            if (temp == '@')
            {
                stx = i;
                sty = j;
            }
        }
    }
    int count = 1;
    queue<pair<int, int>> q;
    q.push({stx, sty});
    vector<vector<bool>> vis(H, vector<bool>(W, false));
    vis[stx][sty] = true;
    while (q.size() > 0)
    {
        int i = q.front().first;
        int j = q.front().second;

        q.pop();
        if (i - 1 >= 0 && !vis[i - 1][j] && grid[i - 1][j] == '.')
        {
            q.push({i - 1, j});
            count++; // top
            vis[i - 1][j] = true;
        }
        if (j + 1 < W && !vis[i][j + 1] && grid[i][j + 1] == '.')
        {
            q.push({i, j + 1}); // r8
            count++;
            vis[i][j + 1] = true;
        }
        if (i + 1 < H && !vis[i + 1][j] && grid[i + 1][j] == '.')
        {
            q.push({i + 1, j}); // bottom
            count++;
            vis[i + 1][j] = true;
        }
        if (j - 1 >= 0 && !vis[i][j - 1] && grid[i][j - 1] == '.')
        {
            q.push({i, j - 1}); // r8
            count++;
            vis[i][j - 1] = true;
        } // left
    }
    cout << count << endl;
}