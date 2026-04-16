#include <iostream>

using namespace std;

long long f(long long x)
{
    long long result[] = {x, 1, x+1, 0};
    return result[x%4];
}

int main()
{
    long long a, b;
    cin >> a >> b;
    cout << (f(a-1) ^ f(b)) << endl;
    return 0;
}