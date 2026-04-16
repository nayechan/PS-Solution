#include <iostream>
#include <vector>
#include <set>

using namespace std;

bool connect(vector<vector<int>>& currentEdge, vector<int>& connection, vector<int> & visit, int visitCnt, int i)
{
    for (int job : currentEdge[i])
    {
        if (visit[job] == visitCnt) continue;

        visit[job] = visitCnt;
        if (connection[job] == -1 || connect(currentEdge, connection, visit, visitCnt, connection[job]))
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

    n*=2;

    vector<vector<int>> currentEdge(n);
    vector<int> currentEdgeIndex(n, -1);

    vector<int> connection(m, -1);

    for (int i = 0;i < n;i+=2)
    {
        int count;
        cin >> count;

        for (int j = 0;j < count;++j)
        {
            int input;
            cin >> input;
            currentEdge[i].push_back(input-1);
            currentEdge[i+1].push_back(input-1);
        }
    }

    int connectionCount = 0;
    int visitCnt = 1;
    vector<int> visit(m, 0);

    for (int i = 0;i < n;++i)
    {
        visitCnt++;
        if(connect(currentEdge, connection, visit, visitCnt, i))
            ++connectionCount;

        if (connectionCount >= m)
            break;
    }

    cout << connectionCount << endl;
    return 0;
}