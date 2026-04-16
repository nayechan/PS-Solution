#include <iostream>
#include <vector>
#include <queue>
#include <memory>

using namespace std;

class Node{
    int index;
    int delay;
    int prevDelay;
    int refCount;
    vector<shared_ptr<Node>> nextNodes;

public:
    Node(int index, int delay)
    {
        this->index = index;
        this->delay = delay;
        prevDelay = 0;
        refCount = 0;
    }

    vector<shared_ptr<Node>> Detach()
    {
        vector<shared_ptr<Node>> zeroDegrees;

        for(auto node : nextNodes)
        {
            node->UpdatePrevDelay(GetTotalDelay());
            node->ReduceRefCount();

            if(node->GetRefCount() == 0)
                zeroDegrees.push_back(node);
        }

        return move(zeroDegrees);
    }

    void AddNode(shared_ptr<Node> node)
    {
        nextNodes.push_back(node);
        node->AddRefCount();
    }

    void AddRefCount()
    {
        ++refCount;
    }

    void ReduceRefCount()
    {
        --refCount;
    }

    int GetRefCount()
    {
        return refCount;
    }

    void UpdatePrevDelay(int prevDelay)
    {
        if(prevDelay > this->prevDelay)
        {
            this->prevDelay = prevDelay;
        }
    }

    int GetDelay(){return delay;}
    int GetTotalDelay(){return delay + prevDelay;}
};

int main()
{
    int t;
    cin >> t;

    for(int _t=0;_t<t;_t++)
    {
        int n, k;
        cin >> n >> k;

        vector<shared_ptr<Node>> nodes(n+1, nullptr);

        for(int i=1;i<=n;++i)
        {
            int delay;
            cin >> delay;

            nodes[i] = make_shared<Node>(i, delay);
        }

        for(int i=0;i<k;++i)
        {
            int x, y;
            cin >> x >> y;

            nodes[x]->AddNode(nodes[y]);
        }

        int w;
        cin >> w;

        auto CompareNode = [](shared_ptr<Node> nodeA, shared_ptr<Node> nodeB){
            return nodeA->GetTotalDelay() > nodeB->GetTotalDelay();
        };

        priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, decltype(CompareNode)> pqueue(CompareNode);

        for(auto node : nodes)
        {
            if(node != nullptr && node->GetRefCount() == 0)
                pqueue.push(node);
        }

        while(!pqueue.empty())
        {
            auto node = pqueue.top();
            pqueue.pop();
            auto nextNodes = node->Detach();

            for(auto _node : nextNodes)
            {
                if(_node->GetRefCount() == 0)
                    pqueue.push(_node);
            }
        }

        
        cout << nodes[w]->GetTotalDelay() << endl;
    }    

    return 0;
}