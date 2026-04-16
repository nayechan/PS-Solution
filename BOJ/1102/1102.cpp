#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <string>

using namespace std;

int solution(vector<vector<int>>& cost, vector<vector<int>>& memo, int current, int statusBit, int target)
{
    if (memo[current][statusBit] != -1)
        return memo[current][statusBit];

    int bit = statusBit;
    int zeroCount = 0;

    int n = cost.size();
    for(int i=0;i<n;++i){
        bool isZero = (bit & 1) == 0;
        if (isZero) ++zeroCount;
        bit = bit >> 1;
    }

    if (zeroCount <= target)
    {
        memo[current][statusBit] = 0;
        return 0;
    }

    bit = statusBit;
    int index = 0;
    int min = INT_MAX;
    for(int i=0;i<n;++i){
        bool isEnabled = (bit & 1) == 1;
        if (!isEnabled)
        {
            int localMin = solution(cost, memo, index, statusBit | (1 << index), target);
            if (localMin == INT_MAX) continue;

            int _bit = statusBit;
            int _index = 0;
            int costMin = INT_MAX;
            for (int j = 0;j < n;++j)
            {
                if ((_bit & 1) == 1)
                {
                    int _cost = cost[j][index];
                    if (costMin > _cost) costMin = _cost;
                }
                ++_index;
                _bit = _bit >> 1;
            }

            if (costMin == INT_MAX) continue;
            localMin += costMin;

            if (min > localMin) min = localMin;
        }
        bit = bit >> 1;
        ++index;
    }

    memo[current][statusBit] = min;
    return min;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> cost(n, vector<int>(n));
    vector<vector<int>> memo(n, vector<int>(1 << n, -1));
    for (int i = 0;i < n;++i)
    {
        for (int j = 0;j < n;++j)
        {
            cin >> cost[i][j];
        }
    }

    string availability;
    cin >> availability;

    int p;
    cin >> p;

    int bit = 0;
    int zeroCount = 0;

    reverse(availability.begin(), availability.end());

    for (auto ch : availability)
    {
        bit = bit << 1;
        if (ch == 'Y')
            ++bit;
        else
            ++zeroCount;
    }

    int index = 0;
    int min = INT_MAX;

    reverse(availability.begin(), availability.end());


    for (auto ch : availability)
    {
        if (ch == 'Y')
        {
            int localMin = solution(cost, memo, index, bit, n-p);
            if (min > localMin) min = localMin;
        }
        ++index;
    }

    int result = min;

    if (zeroCount <= n - p)
        cout << 0;

    else if (result == INT_MAX)
        cout << -1;

    else
        cout << min;

    return 0;
}