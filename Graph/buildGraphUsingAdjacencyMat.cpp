#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int V, E;
    cin >> V >> E;
    vector<vector<int>> mat(V, vector<int>(V, 0));
    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;
        mat[u][v] = 1;
        mat[v][u] = 1;
    }
    cout << "Adjacency Matrix" << endl;
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}