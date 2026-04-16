#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;

    // 11 | 12 | <-12 | 1<-2 | <-1<-2 
    vector<vector<long long>> result(5, vector<long long>(n+1, 0));

    result[0][1] = 1;
    result[1][1] = 1;

    for(int i=2;i<=n;++i)
    {
        result[0][i] = (result[0][i-1] + result[1][i-1] + result[2][i-1] + result[3][i-1] + result[4][i-1]) % 1000000007; // 0, 1
        result[1][i] = (result[0][i-1] + result[1][i-1] + result[2][i-1] + result[3][i-1] + result[4][i-1]) % 1000000007; // 0, 1
        result[2][i] = (result[1][i-1] + result[3][i-1]) % 1000000007; // 1, 3
        result[3][i] = (result[1][i-1] + result[2][i-1]) % 1000000007; // 1, 2
        result[4][i] = result[1][i-1] % 1000000007; // 1
    }

    int sum = 0;

    for(int i=0;i<result.size();++i)
    {
        sum += result[i][n];
        sum %= 1000000007;
    }

    cout << sum << endl;

    return 0;
}