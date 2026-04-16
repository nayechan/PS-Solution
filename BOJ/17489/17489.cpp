#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <climits>

using namespace std;

bool isValid(vector<vector<char>> & map, pair<int,int> pos, int m, int n, char ch)
{
    if(pos.first < 0 || pos.second < 0)
        return false;
    
    if(pos.first >= m || pos.second >= n)
        return false;
    
    return map[pos.first][pos.second] == ch;
}

vector<pair<int,int>> getAccessiblePoint(vector<vector<char>> & map, string route, pair<int,int> currentPoint)
{
    constexpr pair<int,int> delta[] = {
        {0,1},{0,-1},{1,0},{-1,0}
    };

    struct candidate{
        int index;
        pair<int,int> pos;
    };

    queue<candidate> candidatePosition;
    vector<pair<int,int>> result;

    int m = map.size();
    int n = map[0].size();
    int l = route.size();

    candidatePosition.push({0, currentPoint});

    while(!candidatePosition.empty())
    {
        candidate currentCandidate = candidatePosition.front();
        candidatePosition.pop();

        int routeIndex = currentCandidate.index;

        for(int i=0;i<4;++i)
        {
            pair<int,int> nextPos = {
                currentCandidate.pos.first + delta[i].first, currentCandidate.pos.second + delta[i].second
            };


            if(isValid(map, nextPos, m, n, route[routeIndex]))
            {
                if(routeIndex == l - 1)
                {
                    result.push_back(nextPos);
                }

                else
                {
                    candidatePosition.push({routeIndex + 1, nextPos});
                }
            }
        }
    }

    return result;    
}

pair<int, pair<int,int>> getMaxK(set<pair<int,int>> & visited, vector<vector<char>> & map, string route, pair<int,int> currentPoint, int currentK)
{
    visited.insert(currentPoint);
    const auto & nextPoints = getAccessiblePoint(map, route, currentPoint);

    int k = currentK;
    pair<int,int> resultPos = currentPoint;

    for(const auto & nextPoint : nextPoints)
    {
        if(visited.find(nextPoint) != visited.end())
        {
            return {INT_MAX, nextPoint};
        }

        auto result = getMaxK(visited, map, route, nextPoint, currentK + 1);

        if(k < result.first)
        {
            k = result.first;
            resultPos = result.second;
        }

        if(k == INT_MAX) return {INT_MAX, nextPoint};
    }
    visited.erase(currentPoint);
    return {k, resultPos};
}

int main()
{
    int n, m, l;
    cin >> n >> m >> l;

    string route;
    cin >> route;

    vector<vector<char>> map(n, vector<char>(m));

    for(int i=0;i<n;++i)
    {
        for(int j=0;j<m;++j)
        {
            cin >> map[i][j];
        }
    }

    set<pair<int,int>> visitedPoint;

    string subRoute;

    if(l == 1)
    {
        subRoute = route;
    }
    else
    {
        subRoute = route.substr(1);
    }

    const auto & startPoint = getAccessiblePoint(map, subRoute, {0,0});

    struct pointData{
        int k;
        pair<int,int> pos;
    };

    int maxK = 0;
    pair<int,int> resultPos = {0,0};

    for(const auto & point : startPoint)
    {
        auto result = getMaxK(visitedPoint, map, route, point, 1);
        if(maxK < result.first)
        {
            maxK = result.first;
            resultPos = result.second;
        }
        if(maxK == INT_MAX)
        {
            break;
        }
    }

    if (l == 1 && maxK == 0)
    {
        cout << 1 << endl;
        cout << "1 1" << endl;
    }

    else if(maxK == INT_MAX || maxK == 0)
    {
        cout << -1 << endl;
    }

    else
    {
        cout << maxK << endl;
        cout << (resultPos.first+1) << " " << (resultPos.second+1) << endl;
    }

    return 0;
}