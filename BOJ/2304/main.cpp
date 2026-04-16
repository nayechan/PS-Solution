#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> data(1001);

    int _max = 0;
    int maxIndex = -1;

    for(int i=0;i<n;++i)
    {
        int l,h;
        cin >> l >> h;

        data[l] = h;
        if(_max < h)
        {
            _max = h;
            maxIndex = l;
        }
    }

    int current = 0;
    int sum = 0;
    for(int i=0;i<maxIndex;++i)
    {
        current = max(current, data[i]);
        sum += current;
    }

    sum += _max;

    current = 0;
    for(int i=1001;i>maxIndex;--i)
    {
        current = max(current, data[i]);
        sum += current;
    }

    cout << sum << endl;

    return 0;
}