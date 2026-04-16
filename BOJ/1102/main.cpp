#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int solution(vector<vector<int>> & cost, int current, int statusBit, int target)
{
    int bit = statusBit;
    int zeroCount = 0;

    do{
        bool isZero = (bit & 1) == 0;
        if(isZero) ++zeroCount;
        bit = bit >> 1;
    }while(bit > 0);

    if(zeroCount == target)
    {
        return 0;
    }

    bit = statusBit;
    int index = 0;
    int min = INT_MAX;
    do{
        bool isEnabled = (bit & 1) == 1;
        if(!isEnabled)
        {
            int localMin = solution(cost, index, statusBit | (1 << index), target);
            if(localMin == INT_MAX) continue;
            
            localMin += cost[current][index];
            if(min > localMin) min = localMin;
        }
        bit = bit >> 1;
        ++index;
    }while(bit > 0);

    return min;
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> cost(n, vector<int>(n));
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            cin >> cost[i][j];
        }
    }

    string availability;
    cin >> availability;

    int p;
    cin >> p;

    int bit = 0;

    for(auto ch : availability)
    {
        bit = bit << 1;
        if(ch == 'Y')
            ++bit;
    }

    int index = 0;
    int min = INT_MAX;
    for(auto ch : availability)
    {
        if(ch == 'Y')
        {
            int localMin = solution(cost, index, bit, p);
            if(min > localMin) min = localMin;
        }
        ++index;
    }

    cout << min;    

    return 0;
}