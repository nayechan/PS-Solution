#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

struct Edge{
    int a;
    int b;
    int cost;

    Edge(int _a, int _b, int _cost) : a(_a), b(_b), cost(_cost){}
};

struct UnionSet{
    int value;
    int level;
    UnionSet * root;

    UnionSet(int _value) : value(_value), root(this), level(0){}
    
    UnionSet * GetRoot()
    {
        if(root == this) return this;

        root = root->GetRoot();
        return root;
    }

    bool Union(UnionSet * other) {
        UnionSet * root1 = this->GetRoot();
        UnionSet * root2 = other->GetRoot();

        if(root1 == root2) 
            return false;

        if(root1->level < root2->level)
        {
            root1 -> root = root2;
        }
        else
        {
            root2 -> root = root1;
            if (root1->level == root2->level) {
                ++(root1->level);
            }
        }
        return true;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    vector<shared_ptr<UnionSet>> sets(n+1, nullptr);
    vector<Edge> edges, mstEdges;

    for(int i=1;i<=n;++i) sets[i] = make_shared<UnionSet>(i);

    for(int i=0;i<m;++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        
        edges.push_back(Edge(a, b, c));
    }

    sort(edges.begin(), edges.end(), [](const Edge &e1, const Edge &e2){
        return e1.cost < e2.cost;
    });


    for(const auto & edge : edges)
    {
        if (sets[edge.a]->Union(sets[edge.b].get())) {
            mstEdges.push_back(edge);
        }
    }

    mstEdges.pop_back();

    int sum = 0;

    for(const auto & edge : mstEdges)
    {
        sum += edge.cost;
    }    

    cout << sum << endl;

    return 0;
}