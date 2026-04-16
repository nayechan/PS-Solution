#include <iostream>
#include <vector>
#include <set>

using namespace std;

bool connect(vector<vector<int>>& currentEdge, vector<int>& connection, set<int> & visited, int i)
{
    for (int job : currentEdge[i])
    {
        if (visited.find(job) != visited.end()) continue;

        visited.insert(job);
        if (connection[job] == -1 || connect(currentEdge, connection, visited, connection[job]))
        {
            connection[job] = i;
            return true;
        }
    }
    return false;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> currentEdge(n);
    vector<int> currentEdgeIndex(n, -1);

    vector<int> connection(m, -1);

    for (int i = 0;i < n;++i)
    {
        int count;
        cin >> count;

        for (int j = 0;j < count;++j)
        {
            int input;
            cin >> input;
            currentEdge[i].push_back(input-1);
        }
    }

    int connectionCount = 0;

    for (int i = 0;i < n;++i)
    {
        set<int> visited;
        if(connect(currentEdge, connection, visited, i))
            ++connectionCount;
    }

    cout << connectionCount << endl;
    return 0;
}