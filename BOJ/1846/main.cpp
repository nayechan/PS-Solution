#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    if(n <= 3)
    {
        cout << "-1" << endl;
    }

    else
    {
        int mid = n/2;

        for(int i=2;i<=mid;++i)
            cout << i << " ";

        cout << 1 << " ";

        for(int i=mid+2;i<=n;++i)
            cout << i << " ";
        
        cout << mid+1 << endl;
    }


    return 0;
}