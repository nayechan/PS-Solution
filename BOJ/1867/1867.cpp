#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;


bool bm(vector<vector<int>> & connection, vector<int> & connectedNode, 
        vector<int> & visited, int index, int visitCount)
{
    for(auto & con : connection[index])
    {
        if(visited[con] == visitCount)
            continue;
        
        visited[con] = visitCount;

        if(connectedNode[con] == -1 || 
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
    int n, k;
    cin >> n >> k;

    vector<vector<int>> connection(n);
    vector<int> connectedNode(n, -1);
    vector<int> visited(n, -1);

    for(int i=0;i<k;++i)
    {
        int a, b;
        cin >> a >> b;

        connection[a-1].push_back(b-1);
    }

    int connectionCount = 0;
    for(int i=0;i<n;++i)
    {
        if(bm(connection, connectedNode, visited, i, i))
            ++connectionCount;
    }

    cout << connectionCount << endl;

    return 0;
}