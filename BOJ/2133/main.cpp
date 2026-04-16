#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> cases = vector<vector<int>>(3, vector<int>(n+1, 0));
    // 0 : 123, 1: xx<-1, 2: <-1xx

    for(int i=0;i<cases.size();++i)
    {
        if(n >= 2)
            cases[i][2] = 1;
    }

    for(int i=4;i<=n;i+=2)
    {
        cases[0][i] = cases[0][i-2] + cases[1][i-2]+ cases[2][i-2];
        cases[1][i] = cases[0][i-2] + 2 * cases[1][i-2] + cases[2][i-2]; // another case
        cases[2][i] = cases[0][i-2] + cases[1][i-2] + 2 * cases[2][i-2]; // another case
    }

    int sum = 0;

    for(int i=0;i<cases.size();++i)
    {
        sum += cases[i][n];
    }

    cout << sum;

    return 0;
}