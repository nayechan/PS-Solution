#include <iostream>
#include <vector>
#include <map>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

using namespace std;

template <typename T>
class Element
{
    int index;
    T value;
    Element* parent;
    int rank;

public:
    Element(int _index, T _value)
    {
        index = _index;
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
    int GetIndex() { return index; }
};

struct Position {
    long long x, y;

    Position(long long _x = 0, long long _y = 0) {
        x = _x;
        y = _y;
    }

    Position(const Position& position) {
        x = position.x;
        y = position.y;
    }

    bool operator>(const Position& other) const {
        if (x == other.x) {
            return y > other.y;
        }
        return x > other.x;
    }

    bool operator<(const Position& other) const {
        if (x == other.x) {
            return y < other.y;
        }
        return x < other.x;
    }
};

long long ccw(Position p1, Position p2, Position p3) {
    long long s = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y;
    s -= (p1.y * p2.x + p2.y * p3.x + p3.y * p1.x);

    if (s > 0) return 1;
    else if (s == 0) return 0;
    else return -1;
}

struct Segment {
    Position start, end;

    Segment(Position _start, Position _end) {
        start = _start;
        end = _end;
    }
};

bool isIntersecting(Segment segmentA, Segment segmentB) {
    long long ccwA = ccw(segmentA.start, segmentA.end, segmentB.start) * ccw(segmentA.start, segmentA.end, segmentB.end);
    long long ccwB = ccw(segmentB.start, segmentB.end, segmentA.start) * ccw(segmentB.start, segmentB.end, segmentA.end);

    if (ccwA == 0 && ccwB == 0) // Both segments are collinear
    {
        // Check if segments overlap
        if (max(segmentA.start, segmentA.end) < min(segmentB.start, segmentB.end) ||
            max(segmentB.start, segmentB.end) < min(segmentA.start, segmentA.end))
            return false;
        else
            return true;
    }

    return ccwA <= 0 && ccwB <= 0;
}

int main()
{
    int n;

    scanf("%d", &n);
    vector<Element<Segment*>*> segments(n);

    for (int i = 0;i < n;++i)
    {
        int x1, y1, x2, y2;

        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        segments[i] = new Element<Segment*>(i, new Segment(Position(x1, y1), Position(x2, y2)));
    }

    for (int i = 0;i < n - 1;++i)
    {
        for (int j = i + 1;j < n;++j)
        {
            bool intersection = isIntersecting(*(segments[i]->GetValue()), *(segments[j]->GetValue()));

            if (intersection)
            {
                segments[i]->Union(segments[j]);
            }
        }
    }

    map<int, int> elementCount;

    for (int i = 0; i < n; ++i)
    {
        int parentIndex = segments[i]->GetTopParent()->GetIndex();
        if (elementCount.find(parentIndex) == elementCount.end())
        {
            elementCount[parentIndex] = 1;
        }
        else
        {
            ++elementCount[parentIndex];
        }
    }

    printf("%d\n", elementCount.size());

    int max = -1;

    for (auto&& element : elementCount)
    {
        if (element.second > max)
            max = element.second;
    }

    printf("%d\n", max);

    return 0;
}