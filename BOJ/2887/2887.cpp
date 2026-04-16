#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

template <typename T>
class Element
{
    T value;
    Element* parent;
    int rank;

public:
    Element(T _value)
    {
        value = _value;
        parent = nullptr;
        rank = 0;
    }

    void Union(Element* other) {
        Element* thisRoot = GetTopParent();
        Element* otherRoot = other->GetTopParent();

        // Union by rank: attach smaller rank tree under root of higher rank tree
        if (thisRoot != otherRoot) {
            if (thisRoot->rank < otherRoot->rank) {
                thisRoot->parent = otherRoot;
            }
            else if (thisRoot->rank > otherRoot->rank) {
                otherRoot->parent = thisRoot;
            }
            else {
                otherRoot->parent = thisRoot;
                thisRoot->rank++;
            }
        }
    }

    Element* GetRawParent() const {
        return parent;
    }

    Element* GetTopParent() {
        if (parent)
        {
            // 경로 압축
            parent = parent->GetTopParent();
            return parent;
        }
        else return this;
    }

    T GetValue() { return value; }
};

struct Edge{
    int a, b, c;
};

int main()
{
    vector<pair<int,int>> posX, posY, posZ;
    int n;
    cin >> n;

    vector<Element<int>> nodes;
    posX.reserve(n); posY.reserve(n); posZ.reserve(n); nodes.reserve(n);

    for(int i=0;i<n;++i)
    {
        int x,y,z;
        cin >> x >> y >> z;
        posX.push_back({x, i});
        posY.push_back({y, i});
        posZ.push_back({z, i});
        nodes.push_back(Element<int>(i));
    }

    sort(posX.begin(), posX.end());
    sort(posY.begin(), posY.end());
    sort(posZ.begin(), posZ.end());

    auto comp = [](const Edge & a, const Edge & b)
    {
        if(a.c != b.c)
            return a.c > b.c;
        
        if(a.a != b.a)
            return a.a > b.a;
        
        return a.b > b.b;
    };

    priority_queue<Edge, vector<Edge>, decltype(comp)> pqueue(comp);
    int edgeCount = 0;
    int sum = 0;

    for(int i=0;i<n-1;++i)
    {
        pqueue.push({posX[i].second, posX[i+1].second, abs(posX[i+1].first - posX[i].first)});
        pqueue.push({posY[i].second, posY[i+1].second, abs(posY[i+1].first - posY[i].first)});
        pqueue.push({posZ[i].second, posZ[i+1].second, abs(posZ[i+1].first - posZ[i].first)});
    }

    while(edgeCount < n-1)
    {
        const auto element = pqueue.top();
        pqueue.pop();

        if(nodes[element.a].GetTopParent() == nodes[element.b].GetTopParent()) 
        {
            continue;
        }

        nodes[element.a].Union(&nodes[element.b]);
        ++edgeCount;
        sum += element.c;
    }

    cout << sum;
}