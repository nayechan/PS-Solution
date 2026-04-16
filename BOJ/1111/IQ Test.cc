#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;

    int a, b;
    bool indeterminate = true;

    vector<int> data(n);
    for(int i=0;i<n;++i)
    {
        cin >> data[i];
    }

    if(n > 2)
    {
        int diff2 = data[2]-data[1];
        int diff1 = data[1]-data[0];

        if(diff1 != 0)
        {
            if(diff2%diff1 == 0)
            {
                a=diff2/diff1;
                b=data[1]-a*data[0];
                indeterminate = false;
            }
            else
            {
                cout << "B" << endl;
            }
        }
        else
        {
            a=1;
            b=0;
            indeterminate = false;
        }
    }

    else if(n == 2)
    {

        if(data[0]==data[1])
        {
            a=1;
            b=0;
            indeterminate = false;
        }
        else
        {
            cout << "A" << endl;
        }
    }

    else if(n == 1)
    {
        cout << "A" << endl;
    }

    if(!indeterminate)
    {
        int output = data[0];
        for(int i=0;i<n;++i)
        {
            if(output != data[i])
            {
                indeterminate = true;
                break;
            }
            output = a*output+b;
        }
        if(!indeterminate)
        {
            cout << output << endl;
        }
        else
        {
            cout << "B" << endl;
        }
    }


    return 0;
}