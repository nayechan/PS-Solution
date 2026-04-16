#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    long long s, e, sum;
    Node(long long s, long long e, long long sum) :s(s), e(e), sum(sum) {}
};

struct SegTree {
    vector<Node> content;

    long long Sum(long long s, long long e, long long nodeIndex = 1)
    {
        const Node & node = content[nodeIndex];

        if (s > node.e || e < node.s) return 0;
        if (s <= node.s && node.e <= e) return node.sum;

        return Sum(s, e, nodeIndex * 2) + Sum(s, e, nodeIndex * 2 + 1);
    }

    long long Update(long long pos, long long newValue, long long nodeIndex = 1)
    {
        const Node & node = content[nodeIndex];
        if (pos > node.e || pos < node.s) return 0;

        if (pos == node.s && pos == node.e)
        {
            long long diff = newValue - node.sum;
            content[nodeIndex].sum = newValue;
            return diff;
        }

        long long diff = Update(pos, newValue, nodeIndex * 2) + Update(pos, newValue, nodeIndex * 2 + 1);
        content[nodeIndex].sum += diff;
        return diff;
    }

    void Init(vector<long long>& data, long long s, long long e, long long nodeIndex = 1)
    {
        if (s == e)
        {
            content[nodeIndex] = Node(s, e, data[s]);
            return;
        }

        long long mid = (s + e) / 2;

        Init(data, s, mid, nodeIndex * 2);
        Init(data, mid + 1, e, nodeIndex * 2 + 1);

        long long sum = content[nodeIndex * 2].sum + content[nodeIndex * 2 + 1].sum;

        content[nodeIndex] = { s, e, sum };
    }

    SegTree(vector<long long>& data) {
        long long n = data.size();
        content = vector<Node>(n * 4 + 1, Node(-1, -1, -1));
        Init(data, 0, n - 1);
    }

};

int main()
{
    long long n, m, k;
    cin >> n >> m >> k;

    vector<long long> data(n);

    for (long long i = 0;i < n;++i)
    {
        cin >> data[i];
    }

    SegTree segTree(data);

    for (long long i = 0;i < m + k;++i)
    {
        long long a, b, c;
        cin >> a >> b >> c;
        if (a == 1)
        {
            segTree.Update(b - 1, c);
        }
        else
        {
            cout << segTree.Sum(b - 1, c - 1) << endl;
        }
    }
}