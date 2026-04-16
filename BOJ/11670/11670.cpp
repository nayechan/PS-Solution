#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool bm(vector<vector<long long>> & connection, unordered_map<long long, long long> & connectedNode, 
        unordered_map<long long, long long> & visited, int index, int visitCount)
{
    for(auto & con : connection[index])
    {
        auto visitItr = visited.find(con);
        if(visitItr != visited.end() && visitItr->second == visitCount)
            continue;
        
        visited[con] = visitCount;

        if(connectedNode.find(con) == connectedNode.end() || 
            bm(connection, connectedNode, visited, connectedNode[con], visitCount))
        {
            connectedNode[con] = index;
            return true;
        }
    }

    return false;   
}

int main()
{
    int n;
    cin >> n;

    vector<vector<long long>> connection(n);
    vector<pair<long long,long long>> data(n);
    unordered_map<long long, long long> connectedNode;

    for(int i=0;i<n;++i)
    {
        long long a, b;
        cin >> a >> b;
        connection[i].push_back(a+b);
        connection[i].push_back(a-b);
        connection[i].push_back(a*b);
        data[i] = {a,b};
    }

    unordered_map<long long,long long> visited;

    bool success = true;

    for(int i=0;i<n;++i)
    {
        if(!bm(connection, connectedNode, visited, i, i))
        {
            success = false;
            break;
        }
    }

    if(success)
    {
        int index = 0;
        for(const auto & _pair : data)
        {
            long long a = _pair.first, b = _pair.second;
            vector<pair<long long, string>> expressions = {
                {a + b, "+"},
                {a - b, "-"},
                {a * b, "*"}
            };

            for (const auto &expr : expressions)
            {
                auto it = connectedNode.find(expr.first);
                if (it != connectedNode.end() && it->second == index)
                {
                    cout << a << " " << expr.second << " " << b;
                    cout << " = " << expr.first << endl;
                    break;
                }
            }
            ++index;
        }
    }

    else
    {
        cout << "impossible" << endl;
    }

    return 0;
}