#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    vector<vector<long long>> result(n+1, vector<long long>(k+1, 0));

    for(int i=1;i<=n;++i)
    {
        result[i][1] = 1;
    }
    for(int i=1;i<=k;++i)
    {
        result[1][i] = i;
    }

    for(int i=2;i<=n;++i)
    {
        for(int j=2;j<=k;++j)
        {
            result[i][j] = (result[i-1][j] + result[i][j-1]) % 1000000000;
        }
    }

    cout << result[n][k] << endl;
    return 0;
}