#include <iostream>
#include <vector>
#include <climits>

using namespace std;

pair<int, int> solution(vector<vector<int>>& cost, vector<vector<pair<int, int>>>& result, int current, int visition)
{
    if (result[current][visition].second != -1)
        return result[current][visition];

    int index = 0;
    int min = INT_MAX;
    int minFirstIndex = -1;
    while (index < cost.size())
    {
        bool visit = (visition & (1 << index)) != 0;
        if (visit)
        {
            if (cost[index][current] == INT_MAX)
            {
                ++index;
                continue;
            }

            auto subSolution = solution(cost, result, index, visition & ~(1 << current));

            if (subSolution.second == INT_MAX)
            {
                ++index;
                continue;
            }

            int localCost = cost[index][current] + subSolution.second;

            if (localCost < min)
            {
                min = localCost;
                minFirstIndex = subSolution.first;
            }

        }
        ++index;
    }
    result[current][visition] = { minFirstIndex, min };
    return { minFirstIndex, min };
}



int main()
{
    int n;
    cin >> n;
    vector<vector<int>> cost(n, vector<int>(n));
    vector<vector<pair<int, int>>> result(n, vector<pair<int, int>>(1 << n, { -1, -1 }));
    for (int i = 0;i < n;++i)
    {
        for (int j = 0;j < n;++j)
        {
            cin >> cost[i][j];
            if (cost[i][j] == 0) cost[i][j] = INT_MAX;
        }
        result[i][1<<i] = { i, 0 };
    }

    int min = INT_MAX;
    for (int i = 0;i < n;++i)
    {
        pair<int, int> localResult = solution(cost, result, i, (1 << n) - 1);

        if (localResult.first == -1 || cost[i][localResult.first] == INT_MAX || localResult.second == INT_MAX)
            continue;

        int localMin = localResult.second + cost[i][localResult.first];

        if (min > localMin) min = localMin;
    }
    cout << min;
    return 0;
}