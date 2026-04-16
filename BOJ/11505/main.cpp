#include <iostream>
#include <vector>
#include <functional>

using namespace std;

template <typename T>
struct Node {
    int s, e;
    T value;

    Node(int s, int e, T value) : s(s), e(e), value(value) {}
};

template <typename T>
class SegTree {
    vector<Node<T> *> content;
    function<T(const T&, const T&)> aggregator;
    T defaultValue;

    void init(vector<T>& data, int s, int e, int nodeIndex = 1)
    {
        if (s == e)
        {
            content[nodeIndex] = new Node<T>(s, e, data[s]);
            return;
        }

        int mid = (s + e) / 2;
        init(data, s, mid, nodeIndex * 2);
        init(data, mid + 1, e, nodeIndex * 2 + 1);

        T result = aggregator(content[nodeIndex * 2]->value, content[nodeIndex * 2 + 1]->value);

        content[nodeIndex] = new Node<T>(s, e, result);
    }

public:

    const T query(int s, int e, int nodeIndex = 1)
    {
        const Node<T>* node = content[nodeIndex];

        if (s > node->e || e < node->s) return defaultValue;
        if (s <= node->s && node->e <= e) return node->value;

        return aggregator(query(s, e, nodeIndex * 2), query(s, e, nodeIndex * 2 + 1));
    }

    T update(int pos, T value, int nodeIndex = 1)
    {
        Node<T>* node = content[nodeIndex];
        if (pos > node->e || pos < node->s) return node->value;

        if(pos == node->s && pos == node->e)
        {
            node->value = value;
            return value;
        }

        T result = aggregator(update(pos, value, nodeIndex * 2), update(pos, value, nodeIndex * 2 + 1));
        node->value = result;
        return result;
    }

    SegTree(vector<T>& data, function<T(const T &, const T &)> aggregator, T defaultValue)
        : aggregator(aggregator), defaultValue(defaultValue)
    {
        int n = data.size();
        content = vector<Node<T> *>(n * 4 + 1);
        init(data, 0, n - 1);
    }

    ~SegTree()
    {
        for (Node<T>* node : content)
        {
            if(node != nullptr)
                delete node;
        }
    }
};

int main()
{
    long long n, m, k;
    cin >> n >> m >> k;

    // Example data and sum as the aggregator
    vector<long long> data(n);

    for (long long i = 0;i < n;++i)
    {
        cin >> data[i];
    }

    auto mult = [](const long long & a, const long long & b) { return a * b % 1000000007; };

    SegTree<long long> segTree(data, mult, 1);

    for (long long i = 0;i < m + k;++i)
    {
        long long a, b, c;
        cin >> a >> b >> c;
        if (a == 1)
        {
            segTree.update(b - 1, c);
        }
        else
        {
            cout << segTree.query(b - 1, c - 1) << endl;
        }
    }

    return 0;
}