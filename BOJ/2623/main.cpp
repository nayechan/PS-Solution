#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <queue>

using namespace std;

struct Node {
    int index;
    int edgeCount;
    vector<shared_ptr<Node>> nextNode;

    Node(int index) {
        this->index = index;
        this->edgeCount = 0;
    }
};

int main()
{
    int n, m;

    cin >> n >> m;
    cin.ignore();

    vector<shared_ptr<Node>> nodes(n + 1, nullptr);

    for (int i = 1;i <= n;++i)
    {
        nodes[i] = make_shared<Node>(i);
    }

    for (int i = 0;i < m;++i)
    {
        int count;
        cin >> count;

        int a = -1;
        int b = -1;
        cin >> a;

        for (int i = 1; i < count; ++i)
        {
            cin >> b;

            nodes[a]->nextNode.push_back(nodes[b]);
            ++(nodes[b]->edgeCount);

            a = b;
        }
    }

    auto comp = [](shared_ptr<Node> a, shared_ptr<Node> b) {
        return a->edgeCount > b->edgeCount;
        };

    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, decltype(comp)> pqueue(comp);
    vector<int> order;
    int refCount = 0;

    for (auto& nodePtr : nodes)
    {
        if (nodePtr == nullptr) continue;

        if (nodePtr->edgeCount == 0)
        {
            pqueue.push(nodePtr);
        }
    }

    while (!pqueue.empty())
    {
        auto& top = pqueue.top();

        order.push_back(top->index);

        for (auto& connection : top->nextNode)
        {
            --connection->edgeCount;

            if (connection->edgeCount == 0)
            {
                pqueue.push(connection);
            }
        }

        pqueue.pop();
        ++refCount;
    }

    if (refCount != n)
    {
        cout << "0" << endl;
    }
    else
    {
        for (int num : order)
        {
            cout << num << endl;
        }
    }


    cout << endl;

    return 0;
}