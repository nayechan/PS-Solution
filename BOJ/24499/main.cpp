#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    
    int n,k;
    cin >> n >> k;

    vector<int> a(n);

    for(int i=0;i<n;++i)
    {
        cin >> a[i];
    }

    int sum = 0;
    for(int i=0;i<k;++i)
    {
        sum += a[i];
    }

    int max = sum;

    for(int i=1;i<n;++i)
    {
        sum -= a[i-1];
        sum += a[(i+k-1) % n];

        if(max < sum)
            max = sum;
    }

    cout << max;

    return 0;
}

