#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    string a, b;
    getline(cin, a);
    getline(cin, b);    

    int n = b.size();
    vector<int> p(n, 0);

    int len = 0;
    for(int i=1;i<n;++i)
    {
        while(len > 0 && b[len] != b[i])
        {
            len = p[len-1];
        }
        if(b[len] == b[i])
        {
            ++len;
        }
        p[i] = len;
    }

    int m = a.size();
    len = 0;

    vector<int> result;
    for(int i=0;i<m;++i)
    {
        while(len > 0 && b[len] != a[i])
        {
            len = p[len - 1];
        }
        if(b[len] == a[i])
        {
            if(len == n-1)
            {
                result.push_back(i-n+1);
                len = p[len];
            }
            else
            {
                ++len;
            }
        }
    }

    cout << result.size() << "\n";
    for(const auto& e : result)
    {
        cout << e+1 << " ";
    }
    cout << "\n";

    return 0;
}