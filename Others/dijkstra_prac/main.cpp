#include <iostream>
#include <climits>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> distance(n+1, INT_MAX);
    vector<vector<int>> graph(n+1, vector<int>(n+1, INT_MAX));

    for(int i=0;i<m;++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a][b] = c;
        graph[b][a] = c;
    }

    auto comp_pair = [](pair<int,int> & a, pair<int,int> & b){
        return a.first > b.first;
    };

    // .first : cost, .second : index
    priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(comp_pair)> pqueue(comp_pair);

    pqueue.push({0, 1});
    distance[1] = 0;

    while(!pqueue.empty())
    {
        auto element = pqueue.top(); pqueue.pop();

        if(element.first > distance[element.second])
            continue;

        for(int _index = 1; _index <= n; ++_index)
        {
            if(graph[element.second][_index] != INT_MAX && element.first + graph[element.second][_index] < distance[_index])
            {
                distance[_index] = element.first + graph[element.second][_index];
                pqueue.push({distance[_index], _index});
            }
        }
    }

    for(auto dist : distance)
    {
        cout << dist << " ";
    }
    cout << endl;

    return 0;
}