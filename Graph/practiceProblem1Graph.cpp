#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <unordered_set>
using namespace std;
int main()
{
    int n;
    cin >> n;
    cin.ignore();
    vector<string> s;
    for (int i = 0; i < n; i++)
    {

        string temp;
        cin >> temp;
        s.push_back(temp);
    }
    string start, tar;
    cin >> start >> tar;
    unordered_set<string> dict(s.begin(), s.end());
    queue<string> q;
    if (start == tar)
    {
        cout << 0 << endl;
        return 0;
    }
    q.push(start);
    int depth = 1;
    dict.erase(start);
    while (q.size() > 0)
    {
        int levelSize = q.size();
        while (levelSize--)
        {
            string curr = q.front();
            q.pop();
            if (curr == tar)
            {
                cout << depth - 1 << endl;
                return 0;
            }
            for (int i = 0; i < curr.size(); i++)
            {
                string temp = curr;
                for (char c = 'a'; c <= 'z'; c++)
                {
                    temp[i] = c;
                    if (temp == curr)
                    {
                        continue;
                    }
                    if (dict.find(temp) != dict.end())
                    {
                        dict.erase(temp);
                        q.push(temp);
                    }
                }
            }
        }
        depth++;
    }
    cout << -1 << endl;
    return 0;
}