#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

void iterateAllTargetPos(vector<pair<int, int>>& targetPosGroup, set<pair<int, int>>& visitedPos, vector<vector<int>> & data, pair<int, int> pos, int n, int l, int r)
{
    targetPosGroup.push_back(pos);
    visitedPos.insert(pos);
    const vector<pair<int, int>> deltas = {
        {0,1},{0,-1},{1,0},{-1,0}
    };

    for (const auto& delta : deltas)
    {
        pair<int, int> targetPos = { pos.first + delta.first, pos.second + delta.second };
        if (0 <= targetPos.first && targetPos.first < n && 0 <= targetPos.second && targetPos.second < n && visitedPos.find(targetPos) == visitedPos.end())
        {
            int diff = abs(data[targetPos.first][targetPos.second] - data[pos.first][pos.second]);
            if (l <= diff && diff <= r)
            {
                iterateAllTargetPos(targetPosGroup, visitedPos, data, targetPos, n, l, r);
            }
        }
    }
}

int main()
{
    int n, l, r;
    cin >> n >> l >> r;

    vector<vector<int>> data(n, vector<int>(n));

    for (int i = 0;i < n;++i)
    {
        for (int j = 0;j < n;++j)
        {
            cin >> data[i][j];
        }
    }

    bool isMoved = false;
    int day = 0;

    set<pair<int, int>> visitedPos;
    vector<pair<int, int>> targetPosGroup;
    do {
        visitedPos = set<pair<int, int>>();
        isMoved = false;
        for (int i = 0;i < n;++i)
        {
            for (int j = 0;j < n;++j)
            {
                if(visitedPos.find({i,j}) == visitedPos.end())
                    iterateAllTargetPos(targetPosGroup, visitedPos, data, { i,j }, n, l, r);

                if (targetPosGroup.size() > 1)
                {
                    isMoved = true;
                    int sum = 0;
                    for (const auto& targetPos : targetPosGroup)
                    {
                        sum += data[targetPos.first][targetPos.second];
                    }

                    int avg = sum / targetPosGroup.size();

                    for (const auto& targetPos : targetPosGroup)
                    {
                        data[targetPos.first][targetPos.second] = avg;
                    }
                }

                while (!targetPosGroup.empty())
                {
                    targetPosGroup.pop_back();
                }
            }
        }

        if (isMoved)
        {
            ++day;
        }
    } while (isMoved);

    cout << day << endl;
    return 0;
}