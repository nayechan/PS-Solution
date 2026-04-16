#include <iostream>
#include <map>
#include <memory>

using namespace std;

class Node{
    string name;
    string root;
    int level;
    int nodeCount;

public:
    Node(string name){
        this->name = name;
        this->root = name;
        level = 0;
        nodeCount = 1;
    }    

    string GetName(){return name;}
    string GetRoot(){return root;}
    int GetLevel(){return level;}
    int GetNodeCount(){return nodeCount;}
    void SetLevel(int level){this->level = level;}
    void SetRoot(string root){this->root = root;}
    void SetNodeCount(int nodeCount){this->nodeCount = nodeCount;}
};

shared_ptr<Node> find(map<string, shared_ptr<Node>> & nodes, string query)
{
    if(nodes.find(query) != nodes.end() && nodes[query]->GetRoot() == query)
        return nodes[query];
    nodes[query]->SetRoot(find(nodes, nodes[query]->GetRoot())->GetName());
    return nodes[nodes[query]->GetRoot()];
}

void doUnion(map<string, shared_ptr<Node>> & nodes, shared_ptr<Node> nodeA, shared_ptr<Node> nodeB)
{
    auto rootA = find(nodes, nodeA->GetName());
    auto rootB = find(nodes, nodeB->GetName());

    if(rootA->GetName() == rootB->GetName())
        return;

    if(rootA->GetLevel() < rootB->GetLevel())
    {
        rootA->SetRoot(rootB->GetName());
        rootB->SetNodeCount(rootA->GetNodeCount() + rootB->GetNodeCount());
    }

    else
    {
        rootB->SetRoot(rootA->GetName());
        rootA->SetNodeCount(rootA->GetNodeCount() + rootB->GetNodeCount());

        if(rootA->GetLevel() == rootB->GetLevel())
        {
            rootB->SetLevel(rootB->GetLevel() + 1);
        }
    }
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    int t;
    cin >> t;
    for(int _t=0;_t<t;++_t)
    {
        int n;
        cin >> n;
        map<string, shared_ptr<Node>> nodes;
        for(int i=0;i<n;++i)
        {
            string a, b;
            cin >> a >> b;

            if(nodes.find(a) == nodes.end())
                nodes[a] = make_shared<Node>(a);
            if(nodes.find(b) == nodes.end())
                nodes[b] = make_shared<Node>(b);

            doUnion(nodes, nodes[a], nodes[b]);

            cout << find(nodes, a)->GetNodeCount() << '\n';
        }
    }
    return 0;
}