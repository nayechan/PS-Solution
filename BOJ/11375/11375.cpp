#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

void getLevel(vector<int> &level, int personCount, vector<vector<int>> &currentEdge, vector<int> &connection)
{
    queue<int> nextIndex;
    for(int i=0;i<personCount;++i)
    {
        if(connection[i] == -1)
        {
            level[i] = 0;
            nextIndex.push(i);
        }
        else{
            level[i] = INT_MAX;
        }
    }

    while(!nextIndex.empty())
    {
        int currentElement = nextIndex.front();
        int currentLevel = level[currentElement];
        nextIndex.pop();

        for(int job : currentEdge[currentElement])
        {
            int nextElement = connection[job];
            if(nextElement != -1 && level[nextElement] == INT_MAX)
            {
                level[nextElement] = currentLevel + 1;
                nextIndex.push(nextElement);
            }
        }
    }
}

bool connect(vector<vector<int>>& currentEdge, vector<int> &level, vector<int>& connection, int i)
{
    for (int job : currentEdge[i])
    {
        if (connection[job] == -1 || 
            (level[connection[job]] == level[i]+1 && connect(currentEdge, level, connection, connection[job])))
        {
            connection[job] = i;
            connection[i] = job;
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

    vector<vector<int>> currentEdge(n+m);
    vector<int> currentEdgeIndex(n+m, -1);

    vector<int> connection(n+m, -1);

    for (int i = 0;i < n;++i)
    {
        int count;
        cin >> count;

        for (int j = 0;j < count;++j)
        {
            int input;
            cin >> input;
            currentEdge[i].push_back(n+input-1);
            currentEdge[n+input-1].push_back(i);
        }
    }

    vector<int> level(n+m);

    int connectionCount = 0;

    while(true)
    {
        int localConnectionCount = 0;

        getLevel(level, n, currentEdge, connection);

        for (int i = 0;i < n;++i)
        {
            if (connection[i] == -1)
            {
                if(connect(currentEdge, level, connection, i))
                    ++localConnectionCount;
            }
        }

        if(localConnectionCount == 0) break;
        connectionCount += localConnectionCount;
    }

    cout << connectionCount << endl;
    return 0;
}