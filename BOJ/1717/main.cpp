#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Element
{
    T value;
    Element * parent;
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
            } else if (thisRoot->rank > otherRoot->rank) {
                otherRoot->parent = thisRoot;
            } else {
                otherRoot->parent = thisRoot;
                thisRoot->rank++;
            }
        }
    }

    Element* GetRawParent() const {
        return parent;
    }

    Element * GetTopParent(){
        if(parent)
        {
            // 경로 압축
            parent = parent->GetTopParent();
            return parent;
        }
        else return this;
    }

    T GetValue(){return value;}
};

int main()
{

    int n, m;

    scanf("%d %d",&n,&m);

    vector<Element<int>> sets;

    for(int i=0;i<=n;++i)
    {
        sets.push_back(Element<int>(i));
    }

    for(int i=0; i<m; ++i)
    {
        int operation;
        scanf("%d", &operation);

        int a, b;
        scanf("%d %d", &a, &b);

        if(operation == 0)
        {
            sets[a].Union(&sets[b]);
        }
        else
        {
            if(sets[a].GetTopParent()->GetValue() == sets[b].GetTopParent()->GetValue())
            {
                printf("YES\n");
            }
            else
            {
                printf("NO\n");
            }
        }
    }

    return 0;
}