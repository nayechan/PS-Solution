#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;

    vector<vector<int> > data(n+1, vector<int>(2));
    vector<vector<vector<int> > > dp(
        n+1, vector<vector<int>>(k+1, vector<int>(3, -1)));

    for(int i=1;i<=n;++i)
    {
        cin >> data[i][0] >> data[i][1];
    }

    dp[0][0][0] = 0;
    dp[0][0][1] = 0;
    dp[0][0][2] = 0;
    for(int i=1; i<=n; ++i)
    {
        for(int j=0; j<=k; ++j)
        {
            for(int _k=0; _k<3; ++_k)
            {
                int r;
                if(_k == 0)
                {
                    int c1 = max(
                        {dp[i-1][j][0], dp[i-1][j][1], dp[i-1][j][2]}
                    );

                    if(c1 != -1)
                        c1 += data[i][0] + data[i][1];

                    r = c1;
                }
                else if(_k == 1)
                {
                    int c2_1 = j==0 ? -1 : dp[i-1][j-1][0];
                    
                    if(c2_1 != -1) 
                        c2_1 += data[i][0];


                    int c2_2 = j == 0 ? -1 : dp[i-1][j-1][1];

                    if(c2_2 != -1)
                        c2_2 += data[i][0];

                    r = max(c2_1, c2_2);
                }
                else
                {
                    int c2_1 = j==0 ? -1 : dp[i-1][j-1][0];
                    
                    if(c2_1 != -1) 
                        c2_1 += data[i][1];

                    int c2_3 = j == 0 ? -1 : dp[i-1][j-1][2];

                    if(c2_3 != -1)
                        c2_3 += data[i][1];

                    r = max(c2_1, c2_3);
                }

                dp[i][j][_k] = r;
            }
        }
    }

    
    cout << max({dp[n][k][0],dp[n][k][1],dp[n][k][2]}) << '\n';
    //dummy input
    cin >> n >> k;
    return 0;
}