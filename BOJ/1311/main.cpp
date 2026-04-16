#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int solution(int n, int current, int status, vector<vector<int>> & cost, vector<vector<int>> & cache)
{
    if(status == 0)
        return 0;

    if(cache[current][status] != -1)
        return cache[current][status];
    
    int min = INT_MAX;
    for(int i=0;i<n;++i)
    {
        int mask = (1<<i);
        bool notFinished = (status & mask);

        if(!notFinished) continue;

        int localMin = solution(n, ++current, status & ~mask, cost, cache) + cost[current][i];
        if(localMin < min)
            min = localMin;

    }

    return min;    
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> cost(n, vector<int>(n));
    vector<vector<int>> cache(n, vector<int>(1<<n, -1));

    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            cin >> cost[i][j];
        }
    }

    int sum = 0;
    for(int i=0;i<n;++i)
    {
        sum += solution(n, i, 1<<n - 1, cost, cache);
    }

    cout << sum;
}