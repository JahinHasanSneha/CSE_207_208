#include <bits/stdc++.h>
using namespace std;

class Result
{
public:
    long long collisions;
    double averageHits;
};

bool isPrime(int n)
{
    if (n < 2)
    {
        return false;
    }
    if (n % 2 == 0)
    {
        return n == 2;
    }
    for (int i = 3; i * i <= n; i = i + 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
}
const int InitialTableSz = 13;
const double maxLoadFactor = 0.5;
const double minLoadFactor = 0.25;
const int C1 = 1;
const int C2 = 1;

const int Search = 1000;
const int WordLen = 10;
int nextPrime(int n)
{
    if (n <= 2)
    {
        return 2;
    }
    while (!isPrime(n))
    {
        n++;
    }
    return n;
}
int prevPrime(int n)
{
    if (n <= 3)
    {
        return 2;
    }
    while (!isPrime(n))
    {
        n--;
    }
    return n;
}

// Polynomial rolling hash
unsigned long long Hash1(const string &key)
{
    const unsigned long long P = 31;
    unsigned long long hash = 0;

    for (char c : key)
    {
        hash = hash * P + (unsigned char)c;
    }

    return hash;
}
// FNV-1a hash
unsigned long long Hash2(const string &key)
{
    unsigned long long hash =
        14695981039346656037ULL;

    for (char c : key)
    {
        hash ^= (unsigned char)c;
        hash *= 1099511628211ULL;
    }

    return hash;
}
unsigned long long AuxHash(const string &key)
{
    return Hash2(key);
}
enum Method
{
    CHAINING,
    DOUBLE_HASHING,
    CUSTOM_PROBING
};
class Node
{
public:
    string key;
    int val;
    Node *next;
    Node(const string &k, int v)
    {
        key = k;
        val = v;
        next = nullptr;
    }
};
class HashTable
{
    int tableSize;
    int elementCount;
    Method method;
    bool hash1Use;
    vector<Node *> table;
    int insertionSinceExpansion;
    int deletionSinceCompaction;
    long long collisionCount;
    vector<int> HashFreq;
    int primaryHash(const string &key) const
    {
        unsigned long long h;
        if (hash1Use)
        {
            h = Hash1(key);
        }
        else
        {
            h = Hash2(key);
        }
        return h % tableSize;
    }
    int auxiliaryHash(const string &key) const
    {
        unsigned long long h = AuxHash(key);
        return 1 + (h % (tableSize - 1));
    }
    bool expansionAllowed() const
    {
        return insertionSinceExpansion >= max(1, elementCount / 2);
    }
    bool compactionAllowed() const
    {
        return deletionSinceCompaction >= max(1, elementCount / 2);
    }
    void resizeTable(int newS)
    {
        newS = nextPrime(newS);
        vector<Node *> oldTable = table;
        int oldS = tableSize;
        tableSize = newS;
        table.assign(tableSize, nullptr);
        HashFreq.assign(tableSize, 0);
        for (int i = 0; i < oldS; i++)
        {
            Node *cur = oldTable[i];
            while (cur != nullptr)
            {
                Node *next = cur->next;
                int newHashIndex = primaryHash(cur->key);
                HashFreq[newHashIndex]++;
                if (method == Method::CHAINING)
                {
                    cur->next = table[newHashIndex];
                    table[newHashIndex] = cur;
                }
                else
                {
                    int h = primaryHash(cur->key);
                    int step = auxiliaryHash(cur->key);
                    for (int j = 0; j < tableSize; j++)
                    {
                        int index;
                        if (method == Method::DOUBLE_HASHING)
                        {
                            index = (h + 1LL * j * step) % tableSize;
                        }
                        else
                        {
                            index = (h + 1LL * C1 * j * step + 1LL * C2 * j * j) % tableSize;
                        }
                        if (table[index] == nullptr)
                        {
                            table[index] = cur;
                            cur->next = nullptr;
                            break;
                        }
                    }
                }
                cur = next;
            }
        }
    }
    void checkExpansion()
    {
        double loadFactor = (double)elementCount / tableSize;
        if (loadFactor > maxLoadFactor)
        {
            if (expansionAllowed())
            {
                int oldS = tableSize;
                int newS = nextPrime(2 * oldS + 1);
                resizeTable(newS);
                insertionSinceExpansion = 0;
            }
        }
    }
    void checkCompaction()
    {
        if (tableSize == InitialTableSz)
        {
            return;
        }
        double loadFactor = (double)elementCount / tableSize;
        if (loadFactor < minLoadFactor)
        {
            if (compactionAllowed())
            {
                int oldS = tableSize;
                int newS = prevPrime(oldS / 2);
                newS = max(InitialTableSz, newS);
                resizeTable(newS);
                deletionSinceCompaction = 0;
            }
        }
    }
    bool insertChaining(const string& key,int value)
    {
        int index=primaryHash(key);
        Node* cur=table[index];
        while(cur!=nullptr)
        {
            if(cur->key==key)
            {
                return false;
            }
            if(HashFreq[index]>0)
            {
                collisionCount++;
            }
            HashFreq[index]++;
            Node* newN=new Node(key,value);
            newN->next=table[index];
            table[index]=newN;
            return true;
        }
    }
};
int main()
{
}