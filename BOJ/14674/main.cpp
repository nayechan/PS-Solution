#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Data{
    int i;
    int c;
    int h;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    vector<Data> data(n);

    for(int r=0;r<n;++r)
    {
        int i,c,h;
        cin >> i >> c >> h;

        data[i-1] = {i,c,h};
    }

    auto comp = [](const Data &a, const Data &b)
    {
        long long c1 = (long long)a.h*(long long)b.c;
        long long c2 = (long long)b.h*(long long)a.c;
        
        if (c1 == c2)
        {
            if(a.c == b.c)
                return a.i < b.i;

            return a.c < b.c;
        }

        return c1 > c2;
    };

    sort(data.begin(), data.end(), comp);

    for(int i=0;i<k;++i)
    {
        cout << data[i].i << '\n';
    }

    return 0;
}