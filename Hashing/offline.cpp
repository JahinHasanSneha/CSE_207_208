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
        return false;
    if (n % 2 == 0)
        return n == 2;
    for (int i = 3; i * i <= n; i = i + 2)
        if (n % i == 0)
            return false;
    return true;
}

const int InitialTableSz = 13;
const double maxLoadFactor = 0.5;
const double minLoadFactor = 0.25;
const int Ca = 1;
const int Cb = 1;
const int Search = 1000;
const int WordLen = 10;

int nextPrime(int n)
{
    if (n <= 2)
        return 2;
    while (!isPrime(n))
        n++;
    return n;
}

int prevPrime(int n)
{
    if (n <= 3)
        return 2;
    while (!isPrime(n))
        n--;
    return n;
}

// Polynomial rolling hash
unsigned long long Hash1(const string &key)
{
    const unsigned long long P = 31;
    unsigned long long hash = 0;
    for (char c : key)
        hash = hash * P + (unsigned char)c;
    return hash;
}

// FNV-1a hash
unsigned long long Hash2(const string &key)
{
    unsigned long long hash = 14695981039346656037ULL;
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
    int value;
    Node *next;
    Node(const string &k, int v) : key(k), value(v), next(nullptr) {}
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
    vector<int> hashFrequency; // counts keys per primary hash index

    int primaryHash(const string &key) const
    {
        unsigned long long h = hash1Use ? Hash1(key) : Hash2(key);
        return h % tableSize;
    }

    int auxiliaryHash(const string &key) const
    {
        return 1 + (AuxHash(key) % (tableSize - 1));
    }

    bool expansionAllowed() const
    {
        return insertionSinceExpansion >= max(1, elementCount / 2);
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

                if (method == CHAINING)
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
                        int idx;
                        if (method == DOUBLE_HASHING)
                            idx = (h + 1LL * j * step) % tableSize;
                        else
                            idx = (h + 1LL * Ca * j * step + 1LL * Cb * j * j) % tableSize;
                        if (table[idx] == nullptr)
                        {
                            table[idx] = cur;
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
        if (loadFactor > maxLoadFactor && expansionAllowed())
        {
            int newSize = nextPrime(2 * tableSize + 1);
            resizeTable(newSize);
            insertionSinceExpansion = 0;
        }
    }

    void checkCompaction()
    {
        if (tableSize == InitialTableSz)
            return;
        double loadFactor = (double)elementCount / tableSize;
        if (loadFactor < minLoadFactor && compactionAllowed())
        {
            int newSize = prevPrime(tableSize / 2);
            newSize = max(InitialTableSz, newSize);
            newSize = nextPrime(newSize);
            resizeTable(newSize);
            deletionSinceCompaction = 0;
        }
    }

    bool insertChaining(const string &key, int value)
    {
        int index = primaryHash(key);
        Node *cur = table[index];
        while (cur != nullptr)
        {
            if (cur->key == key)
                return false;
            cur = cur->next;
        }
        // Collision if primary hash index already occupied
        if (hashFrequency[index] > 0)
            collisionCount++;
        hashFrequency[index]++;

        Node *newN = new Node(key, value);
        newN->next = table[index];
        table[index] = newN;
        return true;
    }

    // ========== FIXED insertOpenAddressing ==========
    bool insertOpenAddressing(const string &key, int value)
    {
        int h = primaryHash(key);
        int step = auxiliaryHash(key);
        int emptySlot = -1;

        // First pass: check for duplicate and find first empty slot
        for (int i = 0; i < tableSize; i++)
        {
            int idx;
            if (method == DOUBLE_HASHING)
                idx = (h + 1LL * i * step) % tableSize;
            else
                idx = (h + 1LL * Ca * i * step + 1LL * Cb * i * i) % tableSize;

            if (table[idx] == nullptr)
            {
                emptySlot = idx;
                break; // key not present, we have an empty slot
            }
            if (table[idx]->key == key)
                return false; // duplicate – do NOT count collision or increment frequency
        }

        if (emptySlot == -1)
            return false; // table full

        // Now we know the key is new – count primary‑hash collision if any
        if (hashFrequency[h] > 0)
            collisionCount++;
        hashFrequency[h]++;

        table[emptySlot] = new Node(key, value);
        return true;
    }

    void insertWithoutResize(const string &key, int value)
    {
        if (method == CHAINING)
        {
            int index = primaryHash(key);
            Node *newNode = new Node(key, value);
            newNode->next = table[index];
            table[index] = newNode;
        }
        else
        {
            int h = primaryHash(key);
            int step = auxiliaryHash(key);
            for (int i = 0; i < tableSize; i++)
            {
                int idx;
                if (method == DOUBLE_HASHING)
                    idx = (h + 1LL * i * step) % tableSize;
                else
                    idx = (h + 1LL * Ca * i * step + 1LL * Cb * i * i) % tableSize;
                if (table[idx] == nullptr)
                {
                    table[idx] = new Node(key, value);
                    break;
                }
            }
        }
        elementCount++;
    }

public:
    HashTable(Method m, bool hash1)
    {
        method = m;
        hash1Use = hash1;
        tableSize = InitialTableSz;
        elementCount = 0;
        table.assign(tableSize, nullptr);
        hashFrequency.assign(tableSize, 0);
        insertionSinceExpansion = 0;
        deletionSinceCompaction = 0;
        collisionCount = 0;
    }

    void clear()
    {
        for (int i = 0; i < tableSize; i++)
        {
            Node *cur = table[i];
            while (cur != nullptr)
            {
                Node *next = cur->next;
                delete cur;
                cur = next;
            }
            table[i] = nullptr;
        }
    }

    ~HashTable() { clear(); }

    bool insert(const string &key, int value)
    {
        bool inserted = (method == CHAINING) ? insertChaining(key, value)
                                             : insertOpenAddressing(key, value);
        if (!inserted)
            return false;
        elementCount++;
        insertionSinceExpansion++;
        checkExpansion();
        return true;
    }

    pair<bool, int> search(const string &key) const
    {
        int hits = 0;
        if (method == CHAINING)
        {
            int index = primaryHash(key);
            hits++;
            Node *cur = table[index];
            while (cur != nullptr)
            {
                if (cur->key == key)
                    return {true, hits};
                hits++;
                cur = cur->next;
            }
            return {false, hits};
        }
        else
        {
            int h = primaryHash(key);
            int step = auxiliaryHash(key);
            for (int i = 0; i < tableSize; i++)
            {
                int idx;
                if (method == DOUBLE_HASHING)
                    idx = (h + 1LL * i * step) % tableSize;
                else
                    idx = (h + 1LL * Ca * i * step + 1LL * Cb * i * i) % tableSize;
                hits++;
                if (table[idx] == nullptr)
                    return {false, hits};
                if (table[idx]->key == key)
                    return {true, hits};
            }
            return {false, hits};
        }
    }

    bool remove(const string &key)
    {
        if (method == CHAINING)
        {
            int index = primaryHash(key);
            Node *cur = table[index];
            Node *prev = nullptr;
            while (cur != nullptr)
            {
                if (cur->key == key)
                {
                    if (prev == nullptr)
                        table[index] = cur->next;
                    else
                        prev->next = cur->next;
                    delete cur;
                    elementCount--;
                    // ========== FIX: decrement frequency ==========
                    hashFrequency[index]--;
                    deletionSinceCompaction++;
                    checkCompaction();
                    return true;
                }
                prev = cur;
                cur = cur->next;
            }
            return false;
        }
        else
        {
            // Open addressing deletion
            int h = primaryHash(key);
            int step = auxiliaryHash(key);
            int found = -1;
            for (int i = 0; i < tableSize; i++)
            {
                int idx;
                if (method == DOUBLE_HASHING)
                    idx = (h + 1LL * i * step) % tableSize;
                else
                    idx = (h + 1LL * Ca * i * step + 1LL * Cb * i * i) % tableSize;
                if (table[idx] == nullptr)
                    return false;
                if (table[idx]->key == key)
                {
                    found = idx;
                    break;
                }
            }
            if (found == -1)
                return false;

            vector<pair<string, int>> elements;
            for (int i = 0; i < tableSize; i++)
            {
                if (table[i] != nullptr && i != found)
                    elements.push_back({table[i]->key, table[i]->value});
            }
            clear();
            table.assign(tableSize, nullptr);
            elementCount = 0;
            // Reinsert without updating frequency (will rebuild later)
            for (auto &p : elements)
                insertWithoutResize(p.first, p.second);

            elementCount = (int)elements.size();

            // ========== FIX: rebuild hashFrequency ==========
            hashFrequency.assign(tableSize, 0);
            for (int i = 0; i < tableSize; i++)
            {
                if (table[i] != nullptr)
                {
                    int hIdx = primaryHash(table[i]->key);
                    hashFrequency[hIdx]++;
                }
            }

            deletionSinceCompaction++;
            checkCompaction();
            return true;
        }
    }

    int size() const { return elementCount; }
    int getTableSize() const { return tableSize; }
    long long getCollisions() const { return collisionCount; }
};

// --------------------------------------------------
// Random word generation
// --------------------------------------------------
string generateRandomWord(int length, mt19937 &rng)
{
    static const string alpha = "abcdefghijklmnopqrstuvwxyz";
    string word;
    word.reserve(length);
    uniform_int_distribution<int> dist(0, alpha.size() - 1);
    for (int i = 0; i < length; i++)
        word += alpha[dist(rng)];
    return word;
}

vector<string> generateUniqueWords(int count, int length)
{
    random_device rd;
    mt19937 rng(rd());
    unordered_set<string> used;
    vector<string> words;
    words.reserve(count);
    while ((int)words.size() < count)
    {
        string word = generateRandomWord(length, rng);
        if (used.insert(word).second)
            words.push_back(word);
    }
    return words;
}

// --------------------------------------------------
// Experiment
// --------------------------------------------------
Result runExperiment(Method method, bool hash1, const vector<string> &words,
                     const vector<int> &searchIndices)
{
    HashTable ht(method, hash1);
    for (int i = 0; i < (int)words.size(); i++)
        ht.insert(words[i], i + 1);

    long long totalHits = 0;
    int successSearches = 0;
    for (int index : searchIndices)
    {
        auto result = ht.search(words[index]);
        if (result.first)
        {
            totalHits += result.second;
            successSearches++;
        }
    }
    double averageHits = (successSearches > 0) ? (double)totalHits / successSearches : 0.0;
    return {ht.getCollisions(), averageHits};
}

int main()
{
    cout << "Generating 10000 unique words" << endl;
    vector<string> words = generateUniqueWords(10000, WordLen);

    random_device rd;
    mt19937 rng(rd());
    vector<int> searchIndices;
    unordered_set<int> selected;
    uniform_int_distribution<int> dist(0, 10000 - 1);
    while ((int)searchIndices.size() < Search)
    {
        int x = dist(rng);
        if (selected.insert(x).second)
            searchIndices.push_back(x);
    }

    Result chainingHash1 = runExperiment(CHAINING, true, words, searchIndices);
    Result chainingHash2 = runExperiment(CHAINING, false, words, searchIndices);
    Result doubleHashingHash1 = runExperiment(DOUBLE_HASHING, true, words, searchIndices);
    Result doubleHashingHash2 = runExperiment(DOUBLE_HASHING, false, words, searchIndices);
    Result customProbingHash1 = runExperiment(CUSTOM_PROBING, true, words, searchIndices);
    Result customProbingHash2 = runExperiment(CUSTOM_PROBING, false, words, searchIndices);

    cout << "Performance comparison:" << endl;
    cout << left << setw(25) << "Technique"
         << setw(15) << "Hash1 Cols"
         << setw(15) << "Hash1 Hits"
         << setw(15) << "Hash2 Cols"
         << setw(15) << "Hash2 Hits" << endl;
    cout << string(85, '-') << endl;

    cout << left << setw(25) << "Chaining Method"
         << setw(15) << chainingHash1.collisions
         << setw(15) << fixed << setprecision(2) << chainingHash1.averageHits
         << setw(15) << chainingHash2.collisions
         << setw(15) << chainingHash2.averageHits << endl;

    cout << left << setw(25) << "Double Hashing"
         << setw(15) << doubleHashingHash1.collisions
         << setw(15) << doubleHashingHash1.averageHits
         << setw(15) << doubleHashingHash2.collisions
         << setw(15) << doubleHashingHash2.averageHits << endl;

    cout << left << setw(25) << "Custom Probing"
         << setw(15) << customProbingHash1.collisions
         << setw(15) << customProbingHash1.averageHits
         << setw(15) << customProbingHash2.collisions
         << setw(15) << customProbingHash2.averageHits << endl;

    return 0;
}