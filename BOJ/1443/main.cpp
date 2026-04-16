#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

int dfs(int num, int count, int limit, int selection)
{
    int result = 0;

    if(count == 0)
    {
        return num;
    }

    for(int avail = selection; avail<=9; ++avail)
    {
        if(limit >= num*avail)
        {
            int localResult = dfs(num*avail, count-1, limit, avail);
            if(localResult > result) result = localResult;
        }
    }

    return result;
}

int main()
{
    // 98 = 7*7*2 1->9->
    int d,p;
    cin >> d >> p;

    int limit = 1;
    for(int i=0;i<d;++i)
        limit*=10;
    --limit;

    int result = dfs(1, p, limit, 2);
    if(result == 0)
        result = -1;

    cout << result << endl;

    return 0;
}