#include <bits/stdc++.h>
using namespace std;

class AvlNode
{
public:
    int height, key;
    AvlNode *right, *left;
    AvlNode(int K)
    {

        key = K;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};
class AvlTree
{
    AvlNode *root;
    int getHeight(AvlNode *n)
    {
        if (n)
        {
            return n->height;
        }
        else
            return 0;
    }
    void updateHeight(AvlNode *n)
    {
        if (n)
        {
            n->height = 1 + max(getHeight(n->left), getHeight(n->right));
        }
    }
    int getBalance(AvlNode *n)
    {
        if (n)
        {
            return getHeight(n->left) - getHeight(n->right);
        }
        else
            return 0;
    }
    AvlNode *rotateRight(AvlNode *y)
    {
        AvlNode *x = y->left;
        AvlNode *temp = x->right;
        x->right = y;
        y->left = temp;
        updateHeight(y);
        updateHeight(x);
        return x;
    }
    AvlNode *rotateLeft(AvlNode *x)
    {
        AvlNode *y = x->right;
        AvlNode *temp = y->left;
        y->left = x;
        x->right = temp;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AvlNode *insertNode(AvlNode *node, int key, bool &inserted)
    {
        if (!node)
        {
            inserted = true;
            return new AvlNode(key);
        }
        if (key < node->key)
            node->left = insertNode(node->left, key, inserted);
        else if (key > node->key)
            node->right = insertNode(node->right, key, inserted);
        else
        {
            inserted = false;
            return node; // duplicate
        }
        updateHeight(node);
        int balance = getBalance(node);

        // LL
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);
        // RR
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);
        // LR
        if (balance > 1 && key > node->left->key)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // RL
        if (balance < -1 && key < node->right->key)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }
    AvlNode *minValueNode(AvlNode *node)
    {
        AvlNode *cur = node;
        while (cur && cur->left)
        {
            cur = cur->left;
        }
        return cur;
    }
    AvlNode *eraseNode(AvlNode *node, int key, bool &erased)
    {
        if (!node)
        {
            erased = false;
            return nullptr;
        }
        if (key < node->key)
            node->left = eraseNode(node->left, key, erased);
        else if (key > node->key)
            node->right = eraseNode(node->right, key, erased);
        else
        {
            erased = true;
            if (!node->left || !node->right)
            {
                AvlNode *temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            else
            {
                AvlNode *temp = minValueNode(node->right);
                node->key = temp->key;
                node->right = eraseNode(node->right, temp->key, erased);
            }
        }
        if (!node)
            return nullptr;
        updateHeight(node);
        int balance = getBalance(node);
        // LL
        if (balance > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);
        // LR
        if (balance > 1 && getBalance(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // RR
        if (balance < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);
        // RL
        if (balance < -1 && getBalance(node->right) > 0)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }
    bool findNode(AvlNode *node, int key)
    {
        if (!node)
        {
            return false;
        }
        if (key == node->key)
        {
            return true;
        }
        if (key < node->key)
        {
            return findNode(node->left, key);
        }
        return findNode(node->right, key);
    }
    void inorder(AvlNode *node, vector<int> &a)
    {
        if (!node)
        {
            return;
        }
        inorder(node->left, a);
        a.push_back(node->key);
        inorder(node->right, a);
    }
    void destroy(AvlNode *node)
    {
        if (!node)
            return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    string nested(AvlNode *node)
    {
        if (!node)
        {
            return "";
        }
        string left = nested(node->left);
        string right = nested(node->right);
        if (left.empty() && right.empty())
        {
            return to_string(node->key);
        }
        return to_string(node->key) + "(" + left + "," + right + ")";
    }

public:
    AvlTree()
    {
        root = nullptr;
    }
    bool insert(int key)
    {
        bool inserted = false;
        root = insertNode(root, key, inserted);
        return inserted;
    }
    bool find(int key) { return findNode(root, key); }
    bool erase(int key)
    {
        bool erased = false;
        root = eraseNode(root, key, erased);
        return erased;
    }
    vector<int> traverse()
    {
        vector<int> a;
        inorder(root, a);
        return a;
    }
    string serialize() 
    { 
        return nested(root);
     }
     ~AvlTree()
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
    ifstream in(argv[1]);
    ofstream out(argv[2]);
    if (!in || !out)
    {
        return 1;
    }
    AvlTree tree;
    string line;
    long long totalInsert = 0;
    long long totalDelete = 0;
    long long totalFind = 0;
    long long totalTraverse = 0;
    int countInsert = 0;
    int countDelete = 0;
    int countFind = 0;
    int countTraverse = 0;
    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    while (getline(in, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        char operation;
        ss >> operation;

        if (operation == 'I')
        {
            int x;
            ss >> x;
            start = chrono::steady_clock::now();
            bool inserted = tree.insert(x);
            end = chrono::steady_clock::now();
            totalInsert += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            countInsert++;
            if (inserted)
            {
                out << tree.serialize() << endl;
            }
            else
            {
                out << "duplicate" << endl;
            }
        }
        else if (operation == 'D')
        {
            int x;
            ss >> x;
            start = chrono::steady_clock::now();
            bool erased = tree.erase(x);
            end = chrono::steady_clock::now();
            totalDelete += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            countDelete++;
            if (erased)
            {
                out << tree.serialize() << endl;
            }
            else
            {
                out << "not found" << endl;
            }
        }
        else if (operation == 'F')
        {
            int x;
            ss >> x;
            start = chrono::steady_clock::now();
            bool found = tree.find(x);
            end = chrono::steady_clock::now();
            totalFind += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            countFind++;
            if (found)
            {
                out << "found" << endl;
            }
            else
            {
                out << "not found" << endl;
            }
        }
        else if (operation == 'T')
        {
            start = chrono::steady_clock::now();
            vector<int> keys = tree.traverse();
            end = chrono::steady_clock::now();
            totalTraverse += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            countTraverse++;
            for (int i = 0; i < keys.size(); ++i)
            {
                out << keys[i];
                if (i + 1 < keys.size())
                {
                    out << " ";
                }
            }
            out << endl;
        }
    }
    cout << "operation,count,total_ns,average_ns" << endl;
    printStat("insert", countInsert, totalInsert);
    printStat("delete", countDelete, totalDelete);
    printStat("find", countFind, totalFind);
    printStat("traverse", countTraverse, totalTraverse);
    return 0;
}
