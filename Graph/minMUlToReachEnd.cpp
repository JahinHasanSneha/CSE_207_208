#include <bits/stdc++.h>
using namespace std;

void minimumMultiplication(vector<int> &arr, int start, int end)
{
    vector<int> dist(100000, INT_MAX);

    queue<pair<int,int>> q;
    // {node,steps}

    dist[start] = 0;
    q.push({start,0});

    while(!q.empty())
    {
        int u = q.front().first;
        int steps = q.front().second;
        q.pop();

        if(u == end)
        {
            cout << steps << endl;
            return;
        }

        for(auto x : arr)
        {
            int v = (u * x) % 100000;

            if(dist[v] > steps + 1)
            {
                dist[v] = steps + 1;
                q.push({v, steps + 1});
            }
        }
    }

    cout << -1 << endl;
}

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);

    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int start, end;
    cin >> start >> end;

    minimumMultiplication(arr, start, end);

    return 0;
}