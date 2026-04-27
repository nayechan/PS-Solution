#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using ll = long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> l(max(4, n + 1), -1);
    l[1] = 1;
    l[2] = 0;
    l[3] = 1;

    for (int i = 4; i <= n; ++i)
    {
        l[i] = !(l[i - 1] && l[i - 3]);
    }

    cout << (l[n] ? "SK" : "CY") << "\n";


    return 0;
}