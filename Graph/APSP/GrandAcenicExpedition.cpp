#include <bits/stdc++.h>
using namespace std;
int main()
{
    int N, M, Q, A = -1, B = -1;
    cin >> N >> M >> Q;
    vector<int> SScore(N + 1);
    vector<vector<int>> dist(N + 1, vector<int>(N + 1, INT_MAX));
    SScore[0] = -1;
    for (int i = 1; i <= N; i++)
    {
        cin >> SScore[i];
    }
    for (int i = 1; i <= M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = min(w, dist[u][v]);
        dist[v][u] = min(w, dist[v][u]);
    }
    for (int i = 1; i <= N; i++)
    {
        dist[i][i] = 0;
    }
    for (int k = 1; k <= N; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX)
                    continue;

                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    while (Q--)
    {
        int S, T;
        cin >> S >> T;
        A=-1;
        B=-1;
        int MaximumSatisfaction = 0;
        int TotalTravelCost = INT_MAX;
        int ansSA = INT_MAX;
        int ansAB = INT_MAX;
        int ansBT = INT_MAX;
        for (int i = 1; i <= N; i++)
        {
            if (i == S || i == T)
                continue;
            for (int j = 1; j <= N; j++)
            {
                if (j == T || j == S || i == j)
                    continue;
                if (dist[S][i] != INT_MAX && dist[i][j] != INT_MAX && dist[j][T] != INT_MAX)
                {
                    ansSA = dist[S][i];
                    ansAB = dist[i][j];
                    ansBT = dist[j][T];
                    int score = SScore[i] + SScore[j] - dist[S][i] - dist[i][j] - dist[j][T];

                    if (score > MaximumSatisfaction)
                    {
                        MaximumSatisfaction = score;
                        A = i;
                        B = j;
                        TotalTravelCost = dist[S][i] + dist[i][j] + dist[j][T];
                    }
                    else if (score == MaximumSatisfaction)
                    {
                        if (i < A)
                        {
                            TotalTravelCost = dist[S][i] + dist[i][j] + dist[j][T];
                            A = i;
                            B = j;
                        }
                        else if (i == A && j < B)
                        {
                            TotalTravelCost = dist[S][i] + dist[i][j] + dist[j][T];
                            A = i;
                            B = j;
                        }
                    }
                }
            }
        }
        if (ansSA == INT_MAX || ansAB == INT_MAX || ansBT == INT_MAX)
            cout << "NO EXPEDITION" << endl;
        else
        {
            cout << A << " " << B << " " << MaximumSatisfaction << " " << TotalTravelCost << endl;
        }
    }
}