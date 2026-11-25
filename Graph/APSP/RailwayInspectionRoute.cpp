#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;

    vector<vector<int>> dist(N, vector<int>(N, INT_MAX));

    for (int i = 0; i < N; i++)
        dist[i][i] = 0;

    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        dist[u][v] = min(dist[u][v], w);
    }

    int A, B;
    cin >> A >> B;

    // Floyd-Warshall
    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX)
                    continue;

                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    int Q;
    cin >> Q;

    while (Q--)
    {
        int s, d;
        cin >> s >> d;

        int ansA = INT_MAX;
        int ansB = INT_MAX;

        if (dist[s][A] != INT_MAX && dist[A][d] != INT_MAX)
            ansA = dist[s][A] + dist[A][d];

        if (dist[s][B] != INT_MAX && dist[B][d] != INT_MAX)
            ansB = dist[s][B] + dist[B][d];

        if (ansA == INT_MAX && ansB == INT_MAX)
        {
            cout << -1 << endl;
        }
        else if (ansA < ansB)
        {
            cout << ansA << " " << A << endl;
        }
        else if (ansB < ansA)
        {
            cout << ansB << " " << B << endl;
        }
        else
        {
            cout << ansA << " " << min(A, B) << endl;
        }
    }

    return 0;
}