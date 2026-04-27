#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    string a;
    cin >> a;

    vector<int> p(n, 0);

    int len = 0;
    for (int i = 1; i < n; ++i)
    {
        while (len > 0 && a[len] != a[i])
        {
            len = p[len - 1];
        }
        if (a[len] == a[i])
        {
            ++len;
        }
        p[i] = len;
    }

    cout << n - (p[n - 1]) << "\n";

    return 0;
}