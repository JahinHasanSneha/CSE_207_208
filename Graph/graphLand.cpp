#include <bits/stdc++.h>
using namespace std;
vector<int> parent, Rank;

int findParent(int x)
{
    if (parent[x] == x)
        return x;
    return parent[x] = findParent(parent[x]);
}

double dist(pair<int, int> a, pair<int, int> b)
{
    double dx = a.first - b.first;
    double dy = a.second - b.second;
    return sqrt(dx * dx + dy * dy);
}

struct Edge
{
    double w;
    int u, v;
};

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
int main()
{
    int n, r;
    cin >> n >> r;

    vector<Edge> edges;
    vector<pair<double, double>> city(n);
    for (int i = 0; i < n; i++)
    {
        cin >> city[i].first >> city[i].second;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double dx = city[i].first - city[j].first;
            double dy = city[i].second - city[j].second;
            double dist = sqrt(dx * dx + dy * dy);
            edges.push_back({dist, i, j});
        }
    }
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
         { return a.w < b.w; });

    parent.resize(n);
    Rank.assign(n, 0);
    for (int i = 0; i < n; ++i)
        parent[i] = i;

    double roadSum = 0.0, railSum = 0.0;
    int roadCount = 0;
    int used = 0;
    const double eps = 1e-9;

    for (const auto &e : edges)
    {
        if (findParent(e.u) != findParent(e.v))
        {
            unionSet(e.u, e.v);
            if (e.w <= (double)r + eps)
            {
                roadSum += e.w;
                roadCount++;
            }
            else
            {
                railSum += e.w;
            }
            used++;
            if (used == n - 1)
                break;
        }
    }
    int states = n - roadCount;           // each road reduces number of components
    int totalRoad = (int)(roadSum + 0.5); // round to nearest integer
    int totalRail = (int)(railSum + 0.5);

    cout << states << ' ' << totalRoad << ' ' << totalRail << '\n';

    return 0;
}