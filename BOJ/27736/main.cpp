#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int a = 0, r = 0, i = 0;
    for(int t=0;t<n;++t)
    {
        int input;
        cin >> input;
        if(input == 1)
        {
            ++a;
        }
        else if(input == -1)
        {
            ++r;
        }
        else if(input == 0)
        {
            ++i;
        }
    }

    if(i*2 >= n)
    {
        cout << "INVALID" << endl;
    }
    else
    {
        if(a > r)
        {
            cout << "APPROVED" << endl;
        }
        else
        {
            cout << "REJECTED" << endl;
        }
    }
    return 0;
}