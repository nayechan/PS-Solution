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
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;

    vector<vector<int>> currentEdge(n);
    vector<int> currentEdgeIndex(n, -1);

    vector<int> connection(n, -1);

    for (int i = 0;i < m;++i)
    {
        int a, b;
        cin >> a >> b;

        currentEdge[a-1].push_back(b-1);
    }

    int connectionCount = 0;

    for (int i = 0;i < n;++i)
    {
        set<int> visited;
        if(connect(currentEdge, connection, visited, i))
            ++connectionCount;

        if (connectionCount >= m)
            break;
    }

    cout << connectionCount << endl;
    return 0;
}