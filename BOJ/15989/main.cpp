#include <iostream>
#include <vector>

using namespace std;

int test(int n)
{
    vector<int> dp(max(n+1, 3), 1);

    for(int i=2;i<=n;++i)
    {
        dp[i] += dp[i-2];
    }

    for(int i=3;i<=n;++i)
    {
        dp[i] += dp[i-3];
    }

    return dp[n];

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;

    for(int i=0;i<t;++i)
    {
        int n;
        cin >> n;
        cout << test(n) << endl;
    }

    return 0;
}