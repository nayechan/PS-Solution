#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<bool> data(n+1);
    vector<int> changeIndex(n+1, -1);

    data[0] = true;

    for(int i=1;i<=n;++i)
    {
        int op, x, y;
        cin >> op >> x >> y;

        data[i] = (data[y-1] == (op==1) && changeIndex[y-1] <= x-1);

        if(data[i-1] != data[i])
        {
            changeIndex[i] = i;
        }
        else
        {
            changeIndex[i] = changeIndex[i-1];
        }

        cout << (data[i] ? "Yes" : "No") << '\n';
    }

    return 0;
}