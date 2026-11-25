#include <bits/stdc++.h>
using namespace std;

class Interval
{
public:
    int id;
    int start, end;
    int maxEnd;
    Interval *left, *right;
    int height;

    Interval(int id, int s, int e)
    {
        this->id = id;
        start = s;
        end = e;
        maxEnd = e;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class IntervalTree
{
private:
    Interval *root;
    unordered_map<int, pair<int, int>> idInterval; // id -> (start, end)

    int getHeight(Interval *n)
    {
        if (n)
        {
            return n->height;
        }
        else
        {
            return 0;
        }
    }

    int getBalance(Interval *n)
    {
        if (n)
        {
            return getHeight(n->left) - getHeight(n->right);
        }
        else
        {
            return 0;
        }
    }

    int getMaxEnd(Interval *n)
    {
        if (n)
        {
            return n->maxEnd;
        }
        else
        {
            return INT_MIN;
        }
    }

    void update(Interval *n)
    {
        if (!n)
            return;
        n->height = 1 + max(getHeight(n->left), getHeight(n->right));
        n->maxEnd = max({n->end, getMaxEnd(n->left), getMaxEnd(n->right)});
    }

    bool lessKey(Interval *a, int s, int id)
    {
        if (a->start != s)
        {
            return a->start < s;
        }
        else
        {
            return a->id < id;
        }
    }

    Interval *rotateRight(Interval *y)
    {
        Interval *x = y->left;
        Interval *temp = x->right;
        x->right = y;
        y->left = temp;
        update(y);
        update(x);
        return x;
    }

    Interval *rotateLeft(Interval *x)
    {
        Interval *y = x->right;
        Interval *T2 = y->left;
        y->left = x;
        x->right = T2;
        update(x);
        update(y);
        return y;
    }

    Interval *insertNode(Interval *node, int id, int s, int e, bool &inserted)
    {
        if (!node)
        {
            inserted = true;
            idInterval[id] = {s, e};
            return new Interval(id, s, e);
        }

        if (lessKey(node, s, id))
        {
            node->right = insertNode(node->right, id, s, e, inserted);
        }
        else if (s == node->start && id == node->id)
        {
            inserted = false;
            return node;
        }
        else
        {
            node->left = insertNode(node->left, id, s, e, inserted);
        }

        update(node);
        int balance = getBalance(node);

        // LL
        if (balance > 1 && !lessKey(node->left, s, id))
        {
            return rotateRight(node);
        }
        // RR
        if (balance < -1 && lessKey(node->right, s, id))
        {
            return rotateLeft(node);
        }
        // LR
        if (balance > 1 && lessKey(node->left, s, id))
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // RL
        if (balance < -1 && !lessKey(node->right, s, id))
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    Interval *minNode(Interval *node)
    {
        while (node && node->left)
        {
            node = node->left;
        }
        return node;
    }

    Interval *eraseNode(Interval *node, int s, int id, bool &erased)
    {
        if (!node)
        {
            erased = false;
            return nullptr;
        }

        if (lessKey(node, s, id))
        {
            node->right = eraseNode(node->right, s, id, erased);
        }
        else if (s == node->start && id == node->id)
        {
            erased = true;

            if (!node->left || !node->right)
            {
                Interval *temp;
                if (node->left)
                {
                    temp = node->left;
                }
                else
                {
                    temp = node->right;
                }
                delete node;
                return temp;
            }
            else
            {
                Interval *temp = minNode(node->right);
                node->id = temp->id;
                node->start = temp->start;
                node->end = temp->end;
                node->right = eraseNode(node->right, temp->start, temp->id, erased);
            }
        }
        else
        {
            node->left = eraseNode(node->left, s, id, erased);
        }

        if (!node)
            return nullptr;

        update(node);
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
        {
            return rotateRight(node);
        }
        if (balance > 1 && getBalance(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0)
        {
            return rotateLeft(node);
        }
        if (balance < -1 && getBalance(node->right) > 0)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    string nested(Interval *node)
    {
        if (!node)
            return "";
        string left = nested(node->left);
        string right = nested(node->right);
        if (left.empty() && right.empty())
        {
            return to_string(node->id);
        }
        else
        {
            return to_string(node->id) + "(" + left + "," + right + ")";
        }
    }

    void destroy(Interval *node)
    {
        if (!node)
            return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    void collectOverlaps(Interval *node, int s, int e, vector<int> &res)
    {
        if (!node)
            return;
        if (node->left && node->left->maxEnd > s)
        {
            collectOverlaps(node->left, s, e, res);
        }
        if (node->start < e && s < node->end)
        {
            res.push_back(node->id);
        }
        if (node->start >= e)
        {
            return;
        }
        collectOverlaps(node->right, s, e, res);
    }

    int conflictSearch(Interval *node, int s, int e)
    {
        while (node)
        {
          
            if (node->start < e && s < node->end)
                return node->id;

         
            if (node->left && node->left->maxEnd > s)
            {
                node = node->left;
            }
            else
            {
             
                node = node->right;
            }
        }

        return -1;
    }
    void collectAt(Interval *node, int t, vector<int> &res)
    {
        if (!node)
            return;
        if (node->left && node->left->maxEnd > t)
        {
            collectAt(node->left, t, res);
        }
        if (node->start <= t && t < node->end)
        {
            res.push_back(node->id);
        }
        if (node->start > t)
        {
            return;
        }
        collectAt(node->right, t, res);
    }

    Interval *nextSearch(Interval *node, int t)
    {
        if (!node)
            return nullptr;
        if (node->start >= t)
        {
            Interval *leftRes = nextSearch(node->left, t);
            if (leftRes)
            {
                return leftRes;
            }
            else
            {
                return node;
            }
        }
        else
        {
            return nextSearch(node->right, t);
        }
    }

public:
    IntervalTree()
    {
        root = nullptr;
    }

    bool add(int id, int s, int e)
    {
        bool inserted = false;
        root = insertNode(root, id, s, e, inserted);
        return inserted;
    }

    bool remove(int id)
    {
        auto it = idInterval.find(id);
        if (it == idInterval.end())
            return false;

        int s = it->second.first;

        bool erased = false;
        root = eraseNode(root, s, id, erased);

        if (erased)
        {
            idInterval.erase(id);
        }

        return erased;
    }

    bool update(int id, int s, int e)
    {
        auto it = idInterval.find(id);
        if (it == idInterval.end())
            return false;
        int oldS = it->second.first;
        bool erased = false;
        root = eraseNode(root, oldS, id, erased);
        if (!erased)
            return false;
        bool inserted = false;
        root = insertNode(root, id, s, e, inserted);
        return inserted;
    }

    int conflict(int s, int e)
    {
        return conflictSearch(root, s, e);
    }

    vector<int> overlaps(int s, int e)
    {
        vector<int> res;
        collectOverlaps(root, s, e, res);
        return res;
    }

    vector<int> at(int t)
    {
        vector<int> res;
        collectAt(root, t, res);
        return res;
    }

    Interval *next(int t)
    {
        return nextSearch(root, t);
    }

    string serialize()
    {
        return nested(root);
    }

    ~IntervalTree()
    {
        destroy(root);
    }
};

void printStat(const string &name, int cnt, long long total)
{
    cout << name << "," << cnt << "," << total << ",";
    if (cnt > 0)
    {
        cout << total / cnt << endl;
    }
    else
    {
        cout << "N/A" << endl;
    }
}

int main(int argc, char *argv[])
{
    // if (argc != 3)
    // {
    //     cerr << "Usage: " << argv[0] << " <input-file> <output-file>" << endl;
    //     return 1;
    // }

    ifstream in(argv[1]);
    ofstream out(argv[2]);
    if (!in || !out)
    {
        // cerr << "Error opening files." << endl;
        return 1;
    }

    IntervalTree tree;
    int nextId = 1;
    string line;

    long long totalAdd = 0, totalRemove = 0, totalUpdate = 0;
    long long totalConflict = 0, totalOverlaps = 0, totalAt = 0, totalNext = 0;
    int countAdd = 0, countRemove = 0, countUpdate = 0;
    int countConflict = 0, countOverlaps = 0, countAt = 0, countNext = 0;

    while (getline(in, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string cmd;
        ss >> cmd;

        if (cmd == "ADD")
        {
            int s, e;
            ss >> s >> e;
            int id = nextId++;
            auto start = chrono::high_resolution_clock::now();
            bool ok = tree.add(id, s, e);
            auto end = chrono::high_resolution_clock::now();
            totalAdd += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            countAdd++;
            if (ok)
            {
                out << tree.serialize() << endl;
            }
            else
            {
                out << "duplicate" << endl;
            }
        }
        else if (cmd == "REMOVE")
        {
            int id;
            ss >> id;
            auto start = chrono::high_resolution_clock::now();
            bool ok = tree.remove(id);
            auto end = chrono::high_resolution_clock::now();
            totalRemove += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            countRemove++;
            if (ok)
            {
                out << tree.serialize() << endl;
            }
            else
            {
                out << "not found" << endl;
            }
        }
        else if (cmd == "UPDATE")
        {
            int id, s, e;
            ss >> id >> s >> e;
            auto start = chrono::high_resolution_clock::now();
            bool ok = tree.update(id, s, e);
            auto end = chrono::high_resolution_clock::now();
            totalUpdate += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            countUpdate++;
            if (ok)
            {
                out << tree.serialize() << endl;
            }
            else
            {
                out << "not found" << endl;
            }
        }
        else if (cmd == "CONFLICT")
        {
            int s, e;
            ss >> s >> e;
            auto start = chrono::high_resolution_clock::now();
            int conflictId = tree.conflict(s, e);
            auto end = chrono::high_resolution_clock::now();
            totalConflict += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            countConflict++;
            if (conflictId != -1)
            {
                out << "yes" << endl;
            }
            else
            {
                out << "no" << endl;
            }
        }
        else if (cmd == "OVERLAPS")
        {
            int s, e;
            ss >> s >> e;
            auto start = chrono::high_resolution_clock::now();
            vector<int> ids = tree.overlaps(s, e);
            auto end = chrono::high_resolution_clock::now();
            totalOverlaps += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            countOverlaps++;
            if (ids.empty())
            {
                out << "none" << endl;
            }
            else
            {
                for (int i = 0; i < ids.size(); ++i)
                {
                    out << ids[i];
                    if (i + 1 < ids.size())
                    {
                        out << " ";
                    }
                }
                out << endl;
            }
        }
        else if (cmd == "AT")
        {
            int t;
            ss >> t;
            auto start = chrono::high_resolution_clock::now();
            vector<int> ids = tree.at(t);
            auto end = chrono::high_resolution_clock::now();
            totalAt += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            countAt++;
            if (ids.empty())
            {
                out << "none" << endl;
            }
            else
            {
                for (int i = 0; i < ids.size(); ++i)
                {
                    out << ids[i];
                    if (i + 1 < ids.size())
                    {
                        out << " ";
                    }
                }
                out << endl;
            }
        }
        else if (cmd == "NEXT")
        {
            int t;
            ss >> t;
            auto start = chrono::high_resolution_clock::now();
            Interval *nxt = tree.next(t);
            auto end = chrono::high_resolution_clock::now();
            totalNext += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            countNext++;
            if (!nxt)
            {
                out << "none" << endl;
            }
            else
            {
                out << nxt->id << " " << nxt->start << " " << nxt->end << endl;
            }
        }
    }

    cout << "operation,count,total_ns,average_ns" << endl;
    printStat("add", countAdd, totalAdd);
    printStat("remove", countRemove, totalRemove);
    printStat("update", countUpdate, totalUpdate);
    printStat("conflict", countConflict, totalConflict);
    printStat("overlaps", countOverlaps, totalOverlaps);
    printStat("at", countAt, totalAt);
    printStat("next", countNext, totalNext);

    return 0;
}