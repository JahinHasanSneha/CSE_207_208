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
    return true;
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
    CHAINING,DOUBLE_HASHING,CUSTOM_PROBING
};

class Node
{
public:
    string key;
    int value;
    Node *next;
    Node(const string &k, int v)
    {
        key = k;
        value = v;
        next = nullptr;
    }
};

class HashTable
{
    int tableSize;
    int elementCount;
    Method method;
    // true -> Hash1
    // false -> Hash2
    bool hash1Use;

    vector<Node *> table;

    int insertionSinceExpansion;
    int deletionSinceCompaction;

    long long collisionCount;

    // Number of keys whose primary hash maps to each index
    vector<int> hashFrequency;

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
    { return insertionSinceExpansion >= max(1, elementCount / 2);
    }

    bool compactionAllowed() const
    {
        return deletionSinceCompaction >= max(1, elementCount / 2);
    }

    void resizeTable(int newSize)
    {
        newSize = nextPrime(newSize);

        vector<Node *> oldTable = table;
        int oldSize = tableSize;

        tableSize = newSize;

        table.assign(tableSize, nullptr);

        hashFrequency.assign(tableSize, 0);

        for (int i = 0; i < oldSize; i++)
        {
            Node *cur = oldTable[i];

            while (cur != nullptr)
            {
                Node *next = cur->next;

                int newHashIndex = primaryHash(cur->key);
                hashFrequency[newHashIndex]++;
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
                            index =
                                (h + 1LL * j * step) %
                                tableSize;
                        }
                        else
                        {
                            index =
                                (h +
                                 1LL * C1 * j * step +
                                 1LL * C2 * j * j) %
                                tableSize;
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
                int oldSize = tableSize;

                int newSize = nextPrime(2 * oldSize + 1);

                resizeTable(newSize);

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

        double loadFactor =
            (double)elementCount / tableSize;

        if (loadFactor < minLoadFactor)
        {
            if (compactionAllowed())
            {
                int newSize =
                    prevPrime(tableSize / 2);

                newSize =
                    max(InitialTableSz, newSize);

                newSize =
                    nextPrime(newSize);

                resizeTable(newSize);

                deletionSinceCompaction = 0;
            }
        }
    }

    bool insertChaining(
        const string &key,
        int value)
    {
        int index = primaryHash(key);

        Node *cur = table[index];

        while (cur != nullptr)
        {
            if (cur->key == key)
            {
                return false;
            }

            cur = cur->next;
        }

        if (hashFrequency[index] > 0)
        {
            collisionCount++;
        }

        hashFrequency[index]++;

        Node *newN =
            new Node(key, value);

        newN->next = table[index];

        table[index] = newN;

        return true;
    }

    bool insertOpenAddressing(
        const string &key,
        int value)
    {
        int h = primaryHash(key);

        if (hashFrequency[h] > 0)
        {
            collisionCount++;
        }

        hashFrequency[h]++;

        int step = auxiliaryHash(key);

        for (int i = 0;
             i < tableSize;
             i++)
        {
            int index;

            if (method == Method::DOUBLE_HASHING)
            {
                index =
                    (h +
                     1LL * i * step) %
                    tableSize;
            }
            else
            {
                index =
                    (h +
                     1LL * C1 * i * step +
                     1LL * C2 * i * i) %
                    tableSize;
            }

            if (table[index] == nullptr)
            {
                table[index] =
                    new Node(key, value);

                return true;
            }

            if (table[index]->key == key)
            {
                return false;
            }
        }

        return false;
    }

    void insertWithoutResize(
        const string &key,
        int value)
    {
        if (method == Method::CHAINING)
        {
            int index =
                primaryHash(key);

            Node *newNode =
                new Node(key, value);

            newNode->next =
                table[index];

            table[index] =
                newNode;
        }
        else
        {
            int h =
                primaryHash(key);

            int step =
                auxiliaryHash(key);

            for (int i = 0;
                 i < tableSize;
                 i++)
            {
                int index;

                if (method ==
                    Method::DOUBLE_HASHING)
                {
                    index =
                        (h +
                         1LL * i * step) %
                        tableSize;
                }
                else
                {
                    index =
                        (h +
                         1LL * C1 * i * step +
                         1LL * C2 * i * i) %
                        tableSize;
                }

                if (table[index] == nullptr)
                {
                    table[index] =
                        new Node(key, value);

                    break;
                }
            }
        }

        elementCount++;
    }

public:
    HashTable(
        Method m,
        bool hash1)
    {
        method = m;
        hash1Use = hash1;

        tableSize =
            InitialTableSz;

        elementCount = 0;

        table.assign(
            tableSize,
            nullptr);

        hashFrequency.assign(
            tableSize,
            0);

        insertionSinceExpansion = 0;

        deletionSinceCompaction = 0;

        collisionCount = 0;
    }

    void clear()
    {
        for (int i = 0;
             i < tableSize;
             i++)
        {
            Node *cur =
                table[i];

            while (cur != nullptr)
            {
                Node *next =
                    cur->next;

                delete cur;

                cur = next;
            }

            table[i] =
                nullptr;
        }
    }

    ~HashTable()
    {
        clear();
    }

    bool insert(
        const string &key,
        int value)
    {
        bool inserted;

        if (method ==
            Method::CHAINING)
        {
            inserted =
                insertChaining(
                    key,
                    value);
        }
        else
        {
            inserted =
                insertOpenAddressing(
                    key,
                    value);
        }

        if (!inserted)
        {
            return false;
        }

        elementCount++;

        insertionSinceExpansion++;

        checkExpansion();

        return true;
    }

    pair<bool, int>
    search(const string &key) const
    {
        int hits = 0;

        if (method ==
            Method::CHAINING)
        {
            int index =
                primaryHash(key);

            hits++;

            Node *cur =
                table[index];

            while (cur != nullptr)
            {
                if (cur->key == key)
                {
                    return {
                        true,
                        hits};
                }

                hits++;

                cur = cur->next;
            }

            return {
                false,
                hits};
        }

        int h =
            primaryHash(key);

        int step =
            auxiliaryHash(key);

        for (int i = 0;
             i < tableSize;
             i++)
        {
            int index;

            if (method ==
                Method::DOUBLE_HASHING)
            {
                index =
                    (h +
                     1LL * i * step) %
                    tableSize;
            }
            else
            {
                index =
                    (h +
                     1LL * C1 * i * step +
                     1LL * C2 * i * i) %
                    tableSize;
            }

            hits++;

            if (table[index] == nullptr)
            {
                return {
                    false,
                    hits};
            }

            if (table[index]->key == key)
            {
                return {
                    true,
                    hits};
            }
        }

        return {
            false,
            hits};
    }

    bool remove(
        const string &key)
    {
        if (method ==
            Method::CHAINING)
        {
            int index =
                primaryHash(key);

            Node *cur =
                table[index];

            Node *prev =
                nullptr;

            while (cur != nullptr)
            {
                if (cur->key == key)
                {
                    if (prev == nullptr)
                    {
                        table[index] =
                            cur->next;
                    }
                    else
                    {
                        prev->next =
                            cur->next;
                    }

                    delete cur;

                    elementCount--;

                    deletionSinceCompaction++;

                    checkCompaction();

                    return true;
                }

                prev = cur;

                cur = cur->next;
            }

            return false;
        }

        int h =
            primaryHash(key);

        int step =
            auxiliaryHash(key);

        int found = -1;

        for (int i = 0;
             i < tableSize;
             i++)
        {
            int index;

            if (method ==
                Method::DOUBLE_HASHING)
            {
                index =
                    (h +
                     1LL * i * step) %
                    tableSize;
            }
            else
            {
                index =
                    (h +
                     1LL * C1 * i * step +
                     1LL * C2 * i * i) %
                    tableSize;
            }

            if (table[index] == nullptr)
            {
                return false;
            }

            if (table[index]->key == key)
            {
                found = index;
                break;
            }
        }

        if (found == -1)
        {
            return false;
        }

        vector<pair<string, int>>
            elements;

        for (int i = 0;
             i < tableSize;
             i++)
        {
            if (table[i] != nullptr &&
                i != found)
            {
                elements.push_back(
                    {table[i]->key,
                     table[i]->value});
            }
        }

        clear();

        table.assign(
            tableSize,
            nullptr);

        hashFrequency.assign(
            tableSize,
            0);

        elementCount = 0;

        for (auto &p : elements)
        {
            insertWithoutResize(
                p.first,
                p.second);
        }

        elementCount =
            (int)elements.size();

        deletionSinceCompaction++;

        checkCompaction();

        return true;
    }

    int size() const
    {
        return elementCount;
    }

    int getTableSize() const
    {
        return tableSize;
    }

    long long getCollisions() const
    {
        return collisionCount;
    }
};

string generateRandomWord(
    int length,
    mt19937 &rng)
{
    static const string alpha =
        "abcdefghijklmnopqrstuvwxyz";

    string word;

    word.reserve(length);

    uniform_int_distribution<int>
        dist(0, alpha.size() - 1);

    for (int i = 0;
         i < length;
         i++)
    {
        word +=
            alpha[dist(rng)];
    }

    return word;
}

vector<string>
generateUniqueWords(
    int count,
    int length)
{
    random_device rd;

    mt19937 rng(rd());

    unordered_set<string>
        used;

    vector<string>
        words;

    words.reserve(count);

    while ((int)words.size() < count)
    {
        string word =
            generateRandomWord(
                length,
                rng);

        if (used.insert(word).second)
        {
            words.push_back(word);
        }
    }

    return words;
}

Result runExperiment(
    Method method,
    bool hash1,
    const vector<string> &words,
    const vector<int> &searchIndices)
{
    HashTable ht(
        method,
        hash1);

    for (int i = 0;
         i < (int)words.size();
         i++)
    {
        ht.insert(
            words[i],
            i + 1);
    }

    long long totalHits = 0;

    int successSearches = 0;

    for (int index :
         searchIndices)
    {
        auto result =
            ht.search(
                words[index]);

        if (result.first)
        {
            totalHits +=
                result.second;

            successSearches++;
        }
    }

    double averageHits = 0.0;

    if (successSearches > 0)
    {
        averageHits =
            (double)totalHits /
            successSearches;
    }

    return {
        ht.getCollisions(),
        averageHits};
}

int main()
{
    cout
        << "Generating 10000 unique words"
        << endl;

    vector<string> words =
        generateUniqueWords(
            10000,
            WordLen);

    random_device rd;

    mt19937 rng(rd());

    vector<int>
        searchIndices;

    unordered_set<int>
        selected;

    uniform_int_distribution<int>
        dist(0, 10000 - 1);

    while ((int)searchIndices.size() < Search)
    {
        int x =
            dist(rng);

        if (selected.insert(x).second)
        {
            searchIndices.push_back(x);
        }
    }

    Result chainingHash1 =
        runExperiment(
            Method::CHAINING,
            true,
            words,
            searchIndices);

    Result chainingHash2 =
        runExperiment(
            Method::CHAINING,
            false,
            words,
            searchIndices);

    Result doubleHashingHash1 =
        runExperiment(
            Method::DOUBLE_HASHING,
            true,
            words,
            searchIndices);

    Result doubleHashingHash2 =
        runExperiment(
            Method::DOUBLE_HASHING,
            false,
            words,
            searchIndices);

    Result customProbingHash1 =
        runExperiment(
            Method::CUSTOM_PROBING,
            true,
            words,
            searchIndices);

    Result customProbingHash2 =
        runExperiment(
            Method::CUSTOM_PROBING,
            false,
            words,
            searchIndices);

    cout
        << "Performance comparison:"
        << endl;

    cout << left
         << setw(25)
         << "Technique"
         << setw(15)
         << "Hash1 Cols"
         << setw(15)
         << "Hash1 Hits"
         << setw(15)
         << "Hash2 Cols"
         << setw(15)
         << "Hash2 Hits"
         << endl;

    cout
        << string(85, '-')
        << endl;

    cout << left
         << setw(25)
         << "Chaining Method"
         << setw(15)
         << chainingHash1.collisions
         << setw(15)
         << fixed
         << setprecision(2)
         << chainingHash1.averageHits
         << setw(15)
         << chainingHash2.collisions
         << setw(15)
         << chainingHash2.averageHits
         << endl;

    cout << left
         << setw(25)
         << "Double Hashing"
         << setw(15)
         << doubleHashingHash1.collisions
         << setw(15)
         << doubleHashingHash1.averageHits
         << setw(15)
         << doubleHashingHash2.collisions
         << setw(15)
         << doubleHashingHash2.averageHits
         << endl;

    cout << left
         << setw(25)
         << "Custom Probing"
         << setw(15)
         << customProbingHash1.collisions
         << setw(15)
         << customProbingHash1.averageHits
         << setw(15)
         << customProbingHash2.collisions
         << setw(15)
         << customProbingHash2.averageHits
         << endl;

    return 0;
}