#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void func(vector<int> &v, long long a, long long b);

long long gcd(long long a, long long b)
{
    if(b == 0) return a;
    return gcd(b, a%b);
}

int main()
{
    while(true)
    {
        vector<int> arr;
        int a, b;
        cin >> a >> b;

        if (a == 0 && b == 0)
        {
            break;
        }

        func(arr, a, b);
        for(const auto& e: arr)
        {
            cout << e << " ";
        }
        cout << endl;
    }
    return 0;
}

void func(vector<int> &v, long long a, long long b)
{
    while(true)
    {
        long long n = (long long)ceil(b / (float)a);
        // a/b - 1/n = an-b/bn = (an-b) / gcd(an-b, bn) | bn / gcd(an-b, bn)

        long long g;
        while(true){
            g = gcd(a*n-b, b*n);
            if(b*n/g < 1000000) break;
            ++n;
        }

        v.push_back(n);

        a=(a*n-b)/g;
        b=(b*n)/g;

        if(a == 0) break;
    }
}

