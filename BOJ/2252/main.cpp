#include <iostream>
#include <memory>
#include <list>
#include <vector>

using namespace std;

class Node
{
    int index;
    int inDegree;
    vector<shared_ptr<Node>> nextOrder;

public:
    Node(int _index)
    {
        index = _index;
        inDegree = 0;
    }

    int GetIndex()
    {
        return index;
    }

    void AddNext(shared_ptr<Node> node)
    {
        nextOrder.push_back(node);
        node->IncrementInDegree();
    }

    void IncrementInDegree(){++inDegree;}
    void DecrementInDegree(){--inDegree;}

    int GetInDegree() const {
        return inDegree;
    }

    const vector<shared_ptr<Node>>& GetNextOrder() const
    {
        return nextOrder;
    }
};

list<shared_ptr<Node>> FindFirstNodes(vector<shared_ptr<Node>>& nodes)
{
    list<shared_ptr<Node>> firstNodes;

    for(auto && node : nodes)
    {
        if(node == nullptr) continue;

        if(node->GetInDegree() == 0)
            firstNodes.push_back(node);
    }
    return firstNodes;
}

list<shared_ptr<Node>> PerformTopologicalSort(vector<shared_ptr<Node>>& nodes)
{
    list<shared_ptr<Node>> result;
    list<shared_ptr<Node>> && nodeQueue = FindFirstNodes(nodes);

    while (!nodeQueue.empty())
    {
        shared_ptr<Node> node = nodeQueue.front();
        nodeQueue.pop_front();

        result.push_back(node);

        for (auto& nextNode : node->GetNextOrder())
        {
            nextNode->DecrementInDegree();
            if (nextNode->GetInDegree() == 0)
                nodeQueue.push_back(nextNode);
        }
    }

    return result;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    vector<shared_ptr<Node>> nodes(n+1, nullptr);

    for(int i=1;i<=n;++i)
    {
        nodes[i] = make_shared<Node>(i);
    }

    for(int i=0;i<m;++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        nodes[a]->AddNext(nodes[b]);       
    }

    auto result = PerformTopologicalSort(nodes);

    for(auto && element : result)
    {
        printf("%d ",element->GetIndex());
    }
    printf("\n");

    return 0;
}