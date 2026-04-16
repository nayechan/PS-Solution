#include <iostream>
#include <array>
#include <vector>

using namespace std;

int IsPal(vector<vector<int>> & isPal, vector<int> & data, int s, int e)
{
    if(isPal[s][e] == -1)
    {
        if(s == e)
        {
            isPal[s][e] = 1;
        }

        else if(s+1 == e)
        {
            isPal[s][e] = (data[s] == data[e]) ? 1 : 0;
        }

        else
        {
            if(data[s] == data[e] && IsPal(isPal, data, s+1, e-1) == 1)
                isPal[s][e] = 1;
            else
                isPal[s][e] = 0;
        }        
    }

    return isPal[s][e]; 
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> data(n);
    vector<vector<int>> isPal(n, vector<int>(n, -1));

    for(int i=0;i<n;++i)
    {
        cin >> data[i];
    }

    int m;
    cin >> m;

    for(int i=0;i<m;++i)
    {
        int s, e;
        cin >> s >> e;

        cout << IsPal(isPal, data, s-1, e-1) << '\n';
    }
}