#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int main()
{
    long long n;
    long long arr[6];
    vector<vector<bool>> isConnected(6, vector<bool>(6, true));

    for(int i=0;i<=5;++i)
    {
        isConnected[i][i] = false;
        isConnected[i][5-i] = false;
    }
    
    cin >> n;
    for(int i=0;i<6;++i)
    {
        cin >> arr[i];
    }

    if(n == 1)
    {
        int sum = 0;
        for(int i=0;i<6;++i)
        {
            sum+=arr[i];
        }

        int _max=*max_element(arr, arr+6);
        
        cout << sum-_max << endl;
        return 0;
    }

    vector<long long> _min(3, LLONG_MAX);

    _min[0] = *min_element(arr, arr+6);

    for(int i=0;i<6;++i)
    {
        for(int j=0;j<6;++j)
        {
            if(isConnected[i][j])
            {
                long long value = arr[i]+arr[j];
                if(value < _min[1])
                {
                    _min[1] = value;
                }
            }
        }
    }

    for(int i=0;i<6;++i)
    {
        for(int j=0;j<6;++j)
        {
            for(int k=0;k<6;++k)
            {
                if(isConnected[i][j] && isConnected[j][k] && isConnected[k][i])
                {
                    long long value = arr[i]+arr[j]+arr[k];
                    if(value < _min[2])
                    {
                        _min[2] = value;
                    }
                }
            }
        }
    }

    long long blockCount[3] = {4*(n-1)*(n-2)+(n-2)*(n-2), 4*(2*n-3), 4};

    long long result = 0;
    for(int i=0;i<3;++i)
    {
        result += (blockCount[i] * _min[i]);
    }

    cout << result << endl;    

    return 0;
}