#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;

    vector<vector<int>> data(a, vector<int>(b));

    for(int i=0;i<a;++i)
    {
        string input;
        cin >> input;

        int j = 0;
        for(char ch : input)
        {
            if(ch == '1')
                data[i][j] = 0;
            else if(j == 0)
                data[i][j] = 1;
            else
                data[i][j] = data[i][j-1]+1;
            
            ++j;
        }
    }    

    int _max = 0;
    for(int i=0;i<a;++i)
    {
        for(int j=0;j<b;++j)
        {
            int localMin = data[i][j];
            for(int delta=0;delta<=i;++delta)
            {
                localMin = min(localMin, data[i-delta][j]);
                if(_max < localMin * (delta + 1))
                {
                    _max = localMin * (delta + 1);
                }
            }
        }
    }

    cout << _max << endl;

    return 0;
}