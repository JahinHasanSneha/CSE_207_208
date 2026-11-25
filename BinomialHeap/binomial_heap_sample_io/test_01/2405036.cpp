#include <bits/stdc++.h>
using namespace std;
class BinomialNode
{
public:
    int key, degree;
    BinomialNode *parent;
    BinomialNode *child;
    BinomialNode *sibling;
    BinomialNode(int k)
    {
        key = k;
        degree = 0;
        parent = nullptr;
        child = nullptr;
        sibling = nullptr;
    }
};
class BinomialHeap
{
    BinomialNode *head;
    int size;
    unordered_map<int, BinomialNode *> kMap; // decrease key
    BinomialNode *mergeRootList(BinomialNode *h1, BinomialNode *h2)
    {
        BinomialNode dummy(0);
        BinomialNode *tail = &dummy;
        while (h1 && h2)
        {
            if (h1->degree <= h2->degree)
            {
                tail->sibling = h1;
                h1 = h1->sibling;
            }
            else
            {
                tail->sibling = h2;
                h2 = h2->sibling;
            }
            tail = tail->sibling;
        }
        if (h1)
        {
            tail->sibling = h1;
        }
        if (h2)
        {
            tail->sibling = h2;
        }
        return dummy.sibling;
    }
    void link(BinomialNode *parent, BinomialNode *child)
    {
        child->parent = parent;
        child->sibling = parent->child;
        parent->child = child;
        parent->degree++;
    }
    void consolidate()
    {
        if (!head)
            return;

        vector<BinomialNode *> roots;
        for (BinomialNode *cur = head; cur; cur = cur->sibling)
        {
            roots.push_back(cur);
        }

        if (roots.empty())
            return;

        size_t i = 0;
        while (i + 1 < roots.size())
        {
            if (roots[i]->degree != roots[i + 1]->degree)
            {
                i++;
                continue;
            }

            if (i + 2 < roots.size() && roots[i + 2]->degree == roots[i]->degree)
            {
                i++;
                continue;
            }

            BinomialNode *a = roots[i];
            BinomialNode *b = roots[i + 1];
            BinomialNode *parent, *child;

            if (a->key <= b->key)
            {
                parent = a;
                child = b;
            }
            else
            {
                parent = b;
                child = a;
            }

            link(parent, child);

            roots[i] = parent;
            roots.erase(roots.begin() + i + 1);

            if (i > 0 && roots[i - 1]->degree == roots[i]->degree)
            {
                i--;
            }
        }

        for (size_t j = 0; j < roots.size(); j++)
        {
            roots[j]->parent = nullptr;
            roots[j]->sibling = (j + 1 < roots.size()) ? roots[j + 1] : nullptr;
        }
        head = roots[0];
    }

    BinomialNode *findMinNode() const
    {
        if (!head)
            return nullptr;
        BinomialNode *minNode = head;
        for (BinomialNode *cur = head->sibling; cur; cur = cur->sibling)
        {
            if (cur->key < minNode->key)
                minNode = cur;
        }
        return minNode;
    }
    void reverseRootList(BinomialNode *&node)
    {
        BinomialNode *prev = nullptr;
        BinomialNode *cur = node;
        while (cur)
        { //the pointer itself can be changed
            BinomialNode *next = cur->sibling;
            cur->sibling = prev;
            prev = cur;
            cur = next;
        }
        node = prev;
    }
    void collectNodes(BinomialNode *node, vector<BinomialNode *> &nodes) const
    {
        if (!node)
        {
            return;
        }
        nodes.push_back(node);
        collectNodes(node->child, nodes);
        collectNodes(node->sibling, nodes);
    }

    void clear()
    {
        if (!head)
        {
            return;
        }
        vector<BinomialNode *> nodes;
        collectNodes(head, nodes);
        for (auto p : nodes)
        {
            delete p;
        }
        head = nullptr;
        size = 0;
        kMap.clear();
    }

public:
    BinomialHeap()
    {
        head = nullptr;
        size = 0;
    }

    ~BinomialHeap()
    {
        clear();
    }
    void insert(int key)
    {
        BinomialNode *newNode = new BinomialNode(key);
        BinomialHeap temp;
        temp.head = newNode;
        temp.size = 1;
        temp.kMap[key] = newNode;
        unionHeap(temp);
    }
    void decreaseKey(int oldK, int newK)
    {
        auto it = kMap.find(oldK);
        if (it == kMap.end())
        {
            return;
        }
        BinomialNode *node = it->second;
        if (newK >= node->key)
        {
            return;
        }
        node->key = newK;
        kMap.erase(oldK);
        kMap[newK] = node;
        while (node->parent && node->key < node->parent->key)
        {
            int parentKey = node->parent->key;
            node->parent->key = node->key;
            node->key = parentKey;
            kMap[node->parent->key] = node->parent;
            kMap[node->key] = node;
            node = node->parent;
        }
    }
    int findMin() const
    {
        if (!head)
        {
            return INT_MAX;
        }
        return findMinNode()->key;
    }
    int extractMin()
    {
        if (!head)
        {
            return INT_MAX;
        }
        BinomialNode *minNode = findMinNode();
        int minKey = minNode->key;
        if (head == minNode)
        {
            head = minNode->sibling;
        }
        else
        {
            BinomialNode *cur = head;
            while (cur->sibling != minNode)
                cur = cur->sibling;
            cur->sibling = minNode->sibling;
        }
        kMap.erase(minKey);
        BinomialNode *children = minNode->child;
        if (children)
        {
            reverseRootList(children);
            head = mergeRootList(head, children);
        }

        delete minNode;
        size--;

        consolidate();

        return minKey;
    }
    void removeKey(int key)
    {
        decreaseKey(key, -1000000001);
        extractMin();
    }
    void print(ostream &out, int heapIdx) const
    {
        out << "Printing Binomial Heap H" << heapIdx << endl;
        out << "Heap size: " << size << endl;
        if (size == 0)
        {
            out << "Heap H" << heapIdx << " is empty." << endl;
            return;
        }

        BinomialNode *cur = head;
        while (cur)
        {
            out << "Binomial Tree, B" << cur->degree << endl;

            vector<vector<int>> levels;
            vector<BinomialNode *> currentLevel;
            currentLevel.push_back(cur);
            while (!currentLevel.empty())
            {
                vector<int> keys;
                vector<BinomialNode *> nextLevel;
                for (auto node : currentLevel)
                {
                    keys.push_back(node->key);
                    BinomialNode *child = node->child;
                    while (child)
                    {
                        nextLevel.push_back(child);
                        child = child->sibling;
                    }
                }
                sort(keys.begin(), keys.end());
                levels.push_back(keys);
                currentLevel = nextLevel;
            }
            for (size_t lvl = 0; lvl < levels.size(); ++lvl)
            {
                out << "Level " << lvl << ": ";
                for (size_t i = 0; i < levels[lvl].size(); ++i)
                {
                    if (i)
                        out << " ";
                    out << levels[lvl][i];
                }
                out << endl;
            }
            cur = cur->sibling;
        }
    }
    void unionHeap(BinomialHeap &other)
    {
        if (this == &other)
            return;
        head = mergeRootList(head, other.head);
        for (auto &p : other.kMap)
        {
            kMap[p.first] = p.second;
        }
        size += other.size;
        consolidate();
        other.head = nullptr;
        other.size = 0;
        other.kMap.clear();
    }
    unordered_map<int, BinomialNode *> getKMap() const
    {
        return kMap;
    }
    int getSize() const
    {
        return size;
    }
    BinomialNode *getHead() const
    {
        return head;
    }
    void unionHeapWithVisual(BinomialHeap &other, ostream &out)
    {
        if (this == &other)
            return;
        out << "Merged root list (degrees): ";
        BinomialNode *merged = mergeRootList(head, other.head);
        vector<BinomialNode *> roots;
        for (BinomialNode *cur = merged; cur; cur = cur->sibling)
        {
            roots.push_back(cur);
            out << cur->degree << " ";
        }
        out << endl;
        size_t i = 0;
        int step = 1;
        while (i < roots.size())
        {
            if (i + 1 >= roots.size())
            {
                ++i;
                continue;
            }
            if (roots[i]->degree != roots[i + 1]->degree)
            {
                ++i;
                continue;
            }
            if (i + 2 < roots.size() && roots[i + 2]->degree == roots[i]->degree)
            {
                out << "Step " << step++ << ": three B" << roots[i]->degree
                    << " trees, skipping first two" << endl;
                ++i;
                continue;
            }
            BinomialNode *a = roots[i];
            BinomialNode *b = roots[i + 1];
            BinomialNode *parent = (a->key < b->key) ? a : b;
            BinomialNode *child = (a->key < b->key) ? b : a;
            out << "Step " << step++ << ": linking B" << a->degree << " (root " << a->key
                << ") and B" << b->degree << " (root " << b->key << ") -> "
                << "B" << (a->degree + 1) << " with root " << parent->key << endl;

            roots.erase(roots.begin() + i + 1);
            roots.erase(roots.begin() + i);
            link(parent, child);
            roots.insert(roots.begin() + i, parent);
        }
        if (!roots.empty())
        {
            for (size_t j = 0; j < roots.size(); ++j)
            {
                roots[j]->parent = nullptr;
                roots[j]->sibling = (j + 1 < roots.size()) ? roots[j + 1] : nullptr;
            }
            head = roots[0];
        }
        else
        {
            head = nullptr;
        }
        for (auto &p : other.kMap)
        {
            kMap[p.first] = p.second;
        }
        size += other.size;

        other.head = nullptr;
        other.size = 0;
        other.kMap.clear();

        out << "Union complete." << endl;
        out << "Final heap:" << endl;
    }
};
class Visualizer
{
public:
    static void visualizeHeap(const BinomialHeap &heap, std::ostream &out, int heapIndex);
    static void visualizeUnion(BinomialHeap &h1, BinomialHeap &h2, std::ostream &out);

private:
    static void drawTree(BinomialNode *node, std::ostream &out,
                         const std::string &prefix, bool isTail);
    static void printDegreeDistribution(const BinomialHeap &heap, std::ostream &out);
};

void Visualizer::drawTree(BinomialNode *node, std::ostream &out,
                          const std::string &prefix, bool isTail)
{
    if (!node)
        return;
    out << prefix << (isTail ? "└── " : "├── ");
    out << node->key << endl;

    vector<BinomialNode *> children;
    BinomialNode *child = node->child;
    while (child)
    {
        children.push_back(child);
        child = child->sibling;
    }
    for (size_t i = 0; i < children.size(); ++i)
    {
        bool last = (i == children.size() - 1);
        string newPrefix = prefix + (isTail ? "    " : "│   ");
        drawTree(children[i], out, newPrefix, last);
    }
}

void Visualizer::printDegreeDistribution(const BinomialHeap &heap, std::ostream &out)
{
    vector<int> degrees;
    BinomialNode *cur = heap.getHead();
    while (cur)
    {
        degrees.push_back(cur->degree);
        cur = cur->sibling;
    }
    sort(degrees.begin(), degrees.end());
    out << "Root degrees: [";
    for (size_t i = 0; i < degrees.size(); ++i)
    {
        if (i)
            out << ", ";
        out << degrees[i];
    }
    out << "]" << endl;
}

void Visualizer::visualizeHeap(const BinomialHeap &heap, std::ostream &out, int heapIndex)
{
    out << "Visualizing Heap H" << heapIndex << " (size " << heap.getSize() << ")";
    if (heap.getSize() == 0)
    {
        out << "Heap is empty." << endl;
        return;
    }

    BinomialNode *cur = heap.getHead();
    while (cur)
    {
        out << "B" << cur->degree << " tree (root " << cur->key << "):" << endl;
        drawTree(cur, out, "", true);
        cur = cur->sibling;
    }

    printDegreeDistribution(heap, out);
}

void Visualizer::visualizeUnion(BinomialHeap &h1, BinomialHeap &h2, std::ostream &out)
{
    visualizeHeap(h1, out, 1);
    visualizeHeap(h2, out, 2);
    h1.unionHeapWithVisual(h2, out);
    visualizeHeap(h1, out, 1);
}

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");
    if (!infile)
    {
        cerr << "Error. cannot open input.txt" << endl;
        return 1;
    }

    vector<BinomialHeap> heaps(3);

    string line;
    while (std::getline(infile, line))
    {
        if (line.empty())
            continue;
        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (cmd == "I")
        {
            int h, x;
            iss >> h >> x;
            heaps[h].insert(x);
        }
        else if (cmd == "F")
        {
            int h;
            iss >> h;
            int minKey = heaps[h].findMin();
            string msg = "Find Min returned: " + to_string(minKey);
            cout << msg << endl;
            outfile << msg << endl;
        }
        else if (cmd == "E")
        {
            int h;
            iss >> h;
            int minKey = heaps[h].extractMin();
            string msg = "Extract Min returned: " + to_string(minKey);
            cout << msg << endl;
            outfile << msg << endl;
        }
        else if (cmd == "D")
        {
            int h, x, y;
            iss >> h >> x >> y;
            heaps[h].decreaseKey(x, y);
        }
        else if (cmd == "R")
        {
            int h, x;
            iss >> h >> x;
            heaps[h].removeKey(x);
        }
        else if (cmd == "U")
        {
            int h1, h2;
            iss >> h1 >> h2;
            heaps[h1].unionHeap(heaps[h2]);
        }
        else if (cmd == "P")
        {
            int h;
            iss >> h;
            stringstream ss;
            heaps[h].print(ss, h);
            cout << ss.str();
            outfile << ss.str();
        }

        else if (cmd == "V")
        {
            int h;
            iss >> h;
            stringstream ss;
            Visualizer::visualizeHeap(heaps[h], ss, h);
            cout << ss.str();
            outfile << ss.str();
        }
        else if (cmd == "UV")
        {
            int h1, h2;
            iss >> h1 >> h2;
            stringstream ss;
            Visualizer::visualizeUnion(heaps[h1], heaps[h2], ss);
            cout << ss.str();
            outfile << ss.str();
        }
    }

    infile.close();
    outfile.close();
    return 0;
}