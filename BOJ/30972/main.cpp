#include <iostream>
#include <vector>

using namespace std;

int segSum(vector<vector<int>> & data, int r1, int c1, int r2, int c2)
{
    if(r1 == 0 && c1 == 0)
    {
        return data[r2][c2];
    }

    if(r1 == 0)
    {
        return data[r2][c2] - data[r2][c1-1];

    }

    if(c1 == 0)
    {
        return data[r2][c2] - data[r1-1][c2];
    }

    return data[r2][c2] - data[r1-1][c2] - data[r2][c1-1] + data[r1-1][c1-1];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    vector<vector<int>> data(n, vector<int>(n));
    vector<vector<int>> sum(n, vector<int>(n, 0));
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            cin >> data[i][j];
        }
    }

    sum[0][0] = data[0][0];
    for(int i=1;i<n;++i)
    {
        sum[0][i] = sum[0][i-1] + data[0][i];
    }
    for(int i=1;i<n;++i)
    {
        sum[i][0] = sum[i-1][0] + data[i][0];
        int lineSum = data[i][0];
        for(int j=1;j<n;++j)
        {
            sum[i][j] = sum[i-1][j] + lineSum + data[i][j];
            lineSum += data[i][j];
        }
    }

    int q;
    cin >> q;
    for(int i=0;i<q;++i)
    {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        --r1; --c1; --r2; --c2;
        int result = segSum(sum, r1+1, c1+1, r2-1, c2-1) * 2 - segSum(sum, r1, c1, r2, c2);
        cout << result << '\n';
    }

    return 0;
}