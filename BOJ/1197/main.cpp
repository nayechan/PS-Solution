#include <iostream>
#include <memory>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
class Node
{
    T value;
    shared_ptr<Node<T>> root;
    int level;

public:
    Node(T value)
    {
        this->value = value;
        root = nullptr;
        level = 0;
    }

    T getValue(){return value;}
    shared_ptr<Node<T>> getRoot(){
        if(root.get() != this)
        {
            root = root->getRoot();
        }

        return root;
    }
    int getLevel(){return level;}

    void setRoot(shared_ptr<Node<T>> & root){this->root = root;}
    void onAddChild(){++level;}
};

template <typename T>
void unionNodes(shared_ptr<Node<T>>& node1, shared_ptr<Node<T>>& node2) {
    auto root1 = node1->getRoot();
    auto root2 = node2->getRoot();

    if (root1 == root2) return;

    if (root1->getLevel() < root2->getLevel()) {
        root1->setRoot(root2);
    } 
    else 
    {
        root2->setRoot(root1);
        if (root1->getLevel() == root2->getLevel()) {
            root1->onAddChild();
        }
    }
}

struct Edge{
    int weight;
    int a;
    int b;

    Edge(int weight, int a, int b) : weight(weight), a(a), b(b){}
    
    bool operator <(const Edge& other) const
    {
        return weight > other.weight;
    }
};

int main()
{
    priority_queue<Edge> edges;

    int v, e;
    cin >> v >> e;

    vector<shared_ptr<Node<int>>> nodes(v+1, nullptr);
    
    for(int i=1;i<=v;++i)
    {
        nodes[i] = make_shared<Node<int>>(i);
        nodes[i]->setRoot(nodes[i]);
    }

    for(int i=0;i<e;++i)
    {
        int a,b,w;
        cin >> a >> b >> w;
        edges.push(Edge(w, a, b));
    }

    int sum = 0;

    while(!edges.empty())
    {
        auto edge = edges.top();
        edges.pop();

        if(nodes[edge.a]->getRoot() != nodes[edge.b]->getRoot())
        {
            unionNodes(nodes[edge.a], nodes[edge.b]);
            sum += edge.weight;
        }
    }

    cout << sum << endl;

    return 0;
}