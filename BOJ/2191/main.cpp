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

double getDist2(pair<double, double> a, pair<double, double> b)
{
    double xDiff = (a.first - b.first);
    double yDiff = (a.second - b.second);
    return xDiff * xDiff + yDiff * yDiff;
}



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, s, v;
    cin >> n >> m >> s >> v;

    vector<vector<int>> currentEdge(n);
    vector<int> connection(m, -1);
    vector<pair<double,double>> mousePos(n);

    for(int i=0; i<n; ++i)
    {
        cin >> mousePos[i].first >> mousePos[i].second;
    }
    for(int i=0; i<m; ++i)
    {
        pair<double,double> cavePos;
        cin >> cavePos.first >> cavePos.second;

        for(int j=0; j<n; ++j)
        {
            double dist2 = getDist2(mousePos[j], cavePos);
            if(dist2 <= (double)s * s * v * v)
            {
                currentEdge[j].push_back(i);
            }
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

    cout << n - connectionCount << endl;
    return 0;
}