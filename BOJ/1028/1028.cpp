#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;

    vector<vector<bool>> map(m, vector<bool>(n, false));
    vector<vector<int>> rb(m, vector<int>(n, 0));
    vector<vector<int>> lb(m, vector<int>(n, 0));
    vector<vector<int>> result(m, vector<int>(n, 0));

    for(int i=0;i<m;++i)
    {
        string str;
        cin >> str;
        int j = 0;
        for(auto ch : str)
        {
            if(ch == '1')
                map[i][j] = true;
            ++j;
        }
    }

    // / side iteration
    for(int i=0;i<n;++i)
    {
        int length = 1;
        for(int r=0, c=i; r<m && c>=0; ++r, --c)
        {
            if(!map[r][c])
            {
                length = 1;
                continue;
            }
            lb[r][c] = length;
            ++length;
        }
    }
    for(int i=1;i<m;++i)
    {
        int length = 1;
        for(int r=i, c=n-1; r<m && c>=0; ++r, --c)
        {
            if(!map[r][c])
            {
                length = 1;
                continue;
            }
            lb[r][c] = length;
            ++length;
        }
    }

    // \ side iteration
    for(int i=m-1; i>=0; --i)
    {
        int length = 1;
        for(int r=i, c=0; r<m && c<n; ++r, ++c)
        {
            if(!map[r][c])
            {
                length = 1;
                continue;
            }
            rb[r][c] = length;
            ++length;
        }
    }
    for(int i=1; i<n; ++i)
    {
        int length = 1;
        for(int r=0, c=i; r<m && c<n; ++r, ++c)
        {
            if(!map[r][c])
            {
                length = 1;
                continue;
            }
            rb[r][c] = length;
            ++length;
        }
    }

    int _max = 0;
    for(int i=0; i<m; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            int approx = min(lb[i][j], rb[i][j]);
            for(int actual = approx; actual >= 1; --actual)
            {

                int _lb = lb[i-actual+1][j-actual+1];
                int _rb = rb[i-actual+1][j+actual-1];

                if(actual <= _lb && actual <= _rb)
                {
                    _max = max(_max, actual);
                    result[i][j] = actual;
                    break;
                }
            }
        }
    }

    cout << _max << endl;

    return 0;
}