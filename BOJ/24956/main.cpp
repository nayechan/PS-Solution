#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);    

    int n;
    string str;
    cin >> n >> str;

    vector<vector<int>> data(4, vector<int>(n+1,0));

    for(int i=1; i<=n; ++i)
    {
        for(int j=0;j<4;++j)
        {
            data[j][i] = data[j][i-1];
        }
        
        if(str[i-1] == 'W') ++data[0][i];
        if(str[i-1] == 'H') data[1][i] += data[0][i-1];
        if(str[i-1] == 'E')
        {
            data[2][i] += data[1][i-1];
            data[3][i] += ((data[2][i-1] + data[3][i-1]) % 1000000007);
        }
        for(int j=0;j<4;++j)
        {
            data[j][i] %= 1000000007;
        }        
    }
    cout << data[3][n] << endl; 

    return 0;
}