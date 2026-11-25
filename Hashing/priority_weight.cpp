#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

// --------------------------------------------------------------
// 1. Position-weighted hash function (Hash1)
//    returns index in [0, 12] (N = 13 fixed)
// --------------------------------------------------------------
int Hash1(const string &key)
{
    unsigned long long hash = 0;
    for (int i = 0; i < (int)key.size(); i++)
    {
        hash += (i + 1) * (unsigned char)key[i];
    }
    return hash % 13;
}

// --------------------------------------------------------------
// 2. Weight function: (ASCII(first)+ASCII(last)) % 100 / 100.0
// --------------------------------------------------------------
double weight(const string &key)
{
    return (((unsigned char)key[0] + (unsigned char)key[key.size() - 1]) % 100) / 100.0;
}

// --------------------------------------------------------------
// 3. Node for linked list (stores key, value, weight, next)
// --------------------------------------------------------------
class Node
{
public:
    string key;
    int value;
    Node *next;
    double w;
    Node(const string &k, int v, double weight)
        : key(k), value(v), w(weight), next(nullptr) {}
};

// --------------------------------------------------------------
// 4. Hash table with fixed size 13 and sorted chaining
// --------------------------------------------------------------
class HashTable
{
private:
    static const int N = 13;
    vector<Node *> table; // array of chain heads

public:
    HashTable() : table(N, nullptr) {}

    ~HashTable() { clear(); }
    void pringWeight()
    {
        vector<pair<string, string>> pairs = {
            {"cat", "top"}, {"dog", "pot"}, {"bat", "opt"}, {"rat", "art"}, {"sun", "tar"}, {"fun", "run"}};
        for (auto &p : pairs)
        {
            cout << p.first << " "
                 << Hash1(p.first) << " "
                 << fixed << setprecision(2) << weight(p.first) << "     "
                 << p.second << " "
                 << Hash1(p.second) << " "
                 << weight(p.second) << endl;
        }
    }
    // Free all nodes
    void clear()
    {
        for (int i = 0; i < N; i++)
        {
            Node *cur = table[i];
            while (cur)
            {
                Node *tmp = cur->next;
                delete cur;
                cur = tmp;
            }
            table[i] = nullptr;
        }
    }

    // Insert a key-value pair; discard duplicates;
    // maintain descending weight order; stable tie-break for equal weights.
    bool insert(const string &key, int value)
    {
        int idx = Hash1(key);
        double w = weight(key);
        Node *head = table[idx];

        // ----- duplicate check -----
        Node *cur = head;
        while (cur)
        {
            if (cur->key == key)
                return false;
            cur = cur->next;
        }

        // ----- create new node -----
        Node *newNode = new Node(key, value, w);

        // ----- find insertion position -----
        Node *prev = nullptr;
        cur = head;

        // Skip all nodes with weight strictly greater than w
        while (cur && cur->w > w)
        {
            prev = cur;
            cur = cur->next;
        }
        // Skip all nodes with weight equal to w (insert after them → stable tie-break)
        while (cur && cur->w == w)
        {
            prev = cur;
            cur = cur->next;
        }

        // ----- insert -----
        if (prev == nullptr)
        {
            // Insert at head
            newNode->next = head;
            table[idx] = newNode;
        }
        else
        {
            prev->next = newNode;
            newNode->next = cur;
        }
        return true;
    }

    // Print the bucket contents in the required format
    void print() const
    {
        cout << "Bucket Chain (head → tail)\n";

        // Non-empty buckets
        for (int i = 0; i < N; i++)
        {
            if (table[i] != nullptr)
            {
                cout << i << " ";
                Node *cur = table[i];
                bool first = true;
                while (cur)
                {
                    if (!first)
                        cout << " → ";
                    cout << cur->key << " (" << fixed << setprecision(2) << cur->w << ")";
                    first = false;
                    cur = cur->next;
                }
                cout << "\n";
            }
        }

        // Empty buckets (comma-separated list)
        vector<int> empty;
        for (int i = 0; i < N; i++)
        {
            if (table[i] == nullptr)
                empty.push_back(i);
        }
        bool firstEmpty = true;
        for (int idx : empty)
        {
            if (!firstEmpty)
                cout << ",";
            cout << idx;
            firstEmpty = false;
        }
        cout << " (empty)\n";
    }
};

// --------------------------------------------------------------
// 5. Main: insert the 12 given words and print final buckets
// --------------------------------------------------------------
int main()
{
    vector<string> words = {
        "cat", "dog", "bat", "rat", "sun",
        "fun", "run", "top", "pot", "opt",
        "art", "tar"};

    HashTable ht;
    for (int i = 0; i < (int)words.size(); i++)
    {
        ht.insert(words[i], i + 1); // values 1..12
    }
    ht.pringWeight();
    ht.print();
    return 0;
}