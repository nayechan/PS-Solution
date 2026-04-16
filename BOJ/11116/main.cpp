#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;

    for(int i=0;i<n;++i)
    {
        int m;
        cin >> m;

        set<int> a, b;

        for(int i=0;i<m;++i)
        {
            int input;
            cin >> input;
            a.insert(input);
        }

        for(int i=0;i<m;++i)
        {
            int input;
            cin >> input;
            b.insert(input);
        }

        int count = 0;


        for(auto itr = a.begin(); itr!=a.end();)
        {
            int value = *itr;
            ++itr;
            if(a.find(value + 500) != a.end() &&
                b.find(value + 1000) != b.end() &&
                b.find(value + 1500) != b.end())
            {
                ++count;
            }
        }

        cout << count << endl;

    }


    return 0;
}