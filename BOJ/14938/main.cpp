#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <climits>

using namespace std;

struct Node{
    int itemCount;
};

int main()
{
    int n, m, r;

    cin >> n >> m >> r;

    vector<Node> nodes(n+1, Node());
    vector<int> distance(n+1, INT_MAX);
    vector<vector<int>> cost(n+1, vector<int>(n+1, INT_MAX));

    for(int i=1;i<=n;++i)
    {
        cin >> nodes[i].itemCount;
    }

    for(int i=0;i<r;++i)
    {
        int a, b, l;
        cin >> a >> b >> l;
        cost[a][b]=l;
        cost[b][a]=l;
    }

    auto comp = [](pair<int,int> & a, pair<int,int> & b){
        return a.first > b.first;
    };

    //cost, index
    priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(comp)> pqueue(comp);

    int max = 0;

    for(int i=1;i<=n;++i)
    {
        pqueue.push({0,i});
        distance = vector<int>(n+1, INT_MAX);
        distance[i] = 0;
        while(!pqueue.empty())
        {
            auto element = pqueue.top();
            pqueue.pop();

            if(distance[element.second] < element.first)
                continue;
            
            int _index = 0;
            for(auto e : cost[element.second])
            {
                if(e != INT_MAX && distance[element.second] + e < distance[_index])
                {
                    distance[_index] = distance[element.second] + e;
                    pqueue.push({distance[_index], _index});
                }
                ++_index;
            }
        }

        int sum=0;

        for(int j=1;j<=n;++j)
        {
            if(distance[j] <= m)
                sum += nodes[j].itemCount;
        }

        if(sum > max) max = sum;
    }

    cout << max << endl;
    return 0;
}