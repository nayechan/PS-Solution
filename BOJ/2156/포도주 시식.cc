#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using ll = long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> dp(3, vector<int>(n + 1, -1));
    vector<int> data(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> data[i];
    }

    dp[0][0] = 0;

    for (int j = 1; j <= n; ++j)
    {
        dp[0][j] = max({ dp[0][j - 1], dp[1][j-1], dp[2][j-1]});
        for (int i = 1; i <= 2; ++i)
        {
            if(dp[i-1][j-1] != -1)
                dp[i][j] = dp[i - 1][j-1] + data[j-1];
        }
    }

    cout << max({ dp[0][n], dp[1][n], dp[2][n]}) << "\n";


    return 0;
}