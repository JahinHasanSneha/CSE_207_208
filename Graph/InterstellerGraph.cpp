#include <bits/stdc++.h>
using namespace std;
vector<int> parent, Rank;
struct Planet
{
    int id;
    int x, y, z;
};

int findParent(int x)
{
    if (parent[x] == x)
        return x;
    return parent[x] = findParent(parent[x]);
}

void unionSet(int a, int b)
{
    a = findParent(a);
    b = findParent(b);

    if (a == b)
        return;

    if (Rank[a] < Rank[b])
        parent[a] = b;
    else if (Rank[a] > Rank[b])
        parent[b] = a;
    else
    {
        parent[b] = a;
        Rank[a]++;
    }
}

long long kruskal(int V, vector<vector<int>> &edges)
{
    sort(edges.begin(), edges.end());

    parent.resize(V);
    Rank.assign(V, 0);

    for (int i = 0; i < V; i++)
        parent[i] = i;

    long long mstCost = 0;
    int edgesUsed = 0;

    for (auto &e : edges)
    {
        int w = e[0];
        int u = e[1];
        int v = e[2];

        // if (u < 0 || u >= V || v < 0 || v >= V)
        // {
        //     cout << "Error: Invalid vertex index.\n";
        //     return -1;
        // }

        if (findParent(u) != findParent(v))
        {
            mstCost += w;
            unionSet(u, v);
            edgesUsed++;

            if (edgesUsed == V - 1)
                break;
        }
    }

    if (edgesUsed != V - 1)
    {
        cout << "Graph is disconnected. MST does not exist.\n";
        return -1;
    }

    return mstCost;
}
bool cmpX(Planet a, Planet b)
{
    return a.x < b.x;
}
bool cmpY(Planet a, Planet b)
{
    return a.y < b.y;
}
bool cmpZ(Planet a, Planet b)
{
    return a.z < b.z;
}
int main()
{
    int n;
    cin >> n;
    vector<Planet> planets(n);
    for (int i = 0; i < n; i++)
    {
        cin >> planets[i].x >> planets[i].y >> planets[i].z;
        planets[i].id = i;
    }
    vector<vector<int>> edges;
    sort(planets.begin(), planets.end(), cmpX);

    for (int i = 0; i < n - 1; i++)
    {
        edges.push_back({abs(planets[i].x - planets[i + 1].x), planets[i].id, planets[i + 1].id});
    }
    sort(planets.begin(), planets.end(), cmpY);

    for (int i = 0; i < n - 1; i++)
    {
        edges.push_back({abs(planets[i].y - planets[i + 1].y), planets[i].id, planets[i + 1].id});
    }
    sort(planets.begin(), planets.end(), cmpZ);

    for (int i = 0; i < n - 1; i++)
    {
        edges.push_back({abs(planets[i].z - planets[i + 1].z), planets[i].id, planets[i + 1].id});
    }
    cout << kruskal(n, edges) << endl;
    return 0;
}