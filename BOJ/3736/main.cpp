#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

void getLevel(vector<int> &level, int serverCount, vector<vector<int>> &currentEdge, vector<int> &connection)
{
    queue<int> nextIndex;
    for(int i=0;i<serverCount;++i)
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

bool test()
{
    int n;
    cin >> n;

    if(cin.eof()) return false;

    vector<vector<int>> currentEdge(2*n);
    vector<int> currentEdgeIndex(2*n, -1);

    vector<int> connection(2*n, -1);

    for (int i = 0;i < n;++i)
    {
        int job, serverCount; char ch;
        cin >> job >> ch >> ch >> serverCount >> ch;

        for (int j = 0;j < serverCount;++j)
        {
            int input;
            cin >> input;
            currentEdge[input-n].push_back(job+n);
            currentEdge[job+n].push_back(input-n);
        }
    }

    vector<int> level(2*n);

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

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while(test());
    
    return 0;
}