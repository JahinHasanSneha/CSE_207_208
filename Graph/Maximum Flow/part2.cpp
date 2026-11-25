#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int source, int sink, vector<int> &parent, int N)
{

    parent.assign(N, -1);
    parent[source] = -2;
    queue<pair<int, int>> q;
    q.push({source, INT_MAX});

    while (q.size() > 0)
    {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();
        for (int v : adj[u])
        {
            if (parent[v] == -1 && capacity[u][v] > 0)
            {
                parent[v] = u;
                int newFlow = min(flow, capacity[u][v]);
                if (v == sink)
                {
                    return newFlow;
                }
                q.push({v, newFlow});
            }
        }
    }
    return 0;
}
int edmondsKarp(int source, int sink, int N)
{

    int maxFlow = 0;
    vector<int> parent(N);
    int newFlow;
    while ((newFlow = bfs(source, sink, parent, N)) != 0)
    {
        maxFlow += newFlow;
        int cur = sink;
        while (cur != source)
        {
            int prev = parent[cur];
            capacity[prev][cur] -= newFlow;
            capacity[cur][prev] += newFlow;
            cur = prev;
        }
    }
    return maxFlow;
}
void addEdge(int u, int v, int w)
{
    capacity[u][v] += w;
    adj[u].push_back(v);
    adj[v].push_back(u);
}
struct Flight
{
    string DepCity;
    string ArrCity;
    string flightID;
    int depTimeMin;
    int arrTimeMin;
};

int main()
{
    int F;
    cin >> F;
    vector<Flight> flights(F);
    for (int i = 0; i < F; i++)
    {
        string arrTime;
        string depTime;
        cin >> flights[i].flightID >>
            flights[i].DepCity >>
            flights[i].ArrCity >>
            depTime >>
            arrTime;
        flights[i].depTimeMin = stoi(depTime.substr(0, 2)) * 60 + stoi(depTime.substr(3, 2));
        flights[i].arrTimeMin = stoi(arrTime.substr(0, 2)) * 60 + stoi(arrTime.substr(3, 2));
    }

    vector<vector<int>> dag(F);
    for (int i = 0; i < F; i++)
    {
        for (int j = 0; j < F; j++)
        {
            if (i == j)
            {
                continue;
            }
            if (flights[i].ArrCity == flights[j].DepCity && flights[i].arrTimeMin + 180 <= flights[j].depTimeMin)
            {
                dag[i].push_back(j);
            }
        }
    }int nodes = 2 * F + 2;
    int S = 2 * F;
    int T = 2 * F + 1;
    capacity.assign(nodes, vector<int>(nodes, 0));
    adj.assign(nodes, vector<int>());

    for (int i = 0; i < F; i++)
    {
        addEdge(S, i, 1);
    }

    for (int i = 0; i < F; i++)
    {
        addEdge(F + i, T, 1);
    }

    for (int i = 0; i < F; i++)
    {
        for (int j : dag[i])
        {
            addEdge(i, F + j, 1);
        }
    }
    int matching = edmondsKarp(S, T, nodes);
    int minAirCraft = F - matching;
    cout << "Number of Aircraft:" << minAirCraft << endl;
    vector<int> parent(F, -1);
    vector<int> child(F, -1);
    for (int u = 0; u < F; u++)
    {
        for (int v : adj[u])
        {
            if (v >= F && v < 2 * F)
            {
                int flight = v - F;
                if (capacity[u][v] == 0 && capacity[v][u] == 1)
                {
                    child[u] = flight;
                    parent[flight] = u;
                }
            }
        }
    }
    vector<int> routes;
    for (int i = 0; i < F; i++)
    {
        if (parent[i] == -1)
        {
            routes.push_back(i);
        }
    }
    int airCraftNumber = 1;
    for (int st : routes)
    {
        cout << "Aircraft " << airCraftNumber++ << ": ";
        int curr = st;
        bool first = true;
        while (curr != -1)
        {
            if (!first)
            {
                cout << "->";
            }

            cout << flights[curr].flightID;
            first = false;
            curr = child[curr];
        }
        cout << endl;
    }
}
