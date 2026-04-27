#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using ll = long long;
constexpr ll FENWICK_SIZE = (1 << 20);
ll fenwick[FENWICK_SIZE + 1];

ll query(int idx)
{
    ll result = 0;
    while (idx)
    {
        result += fenwick[idx];
        idx -= idx & (-idx);
    }

    return result;
}

void update(int idx, ll value)
{
    while (idx <= FENWICK_SIZE)
    {
        fenwick[idx] += value;
        idx += idx & (-idx);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i)
    {
        int op;
        cin >> op;

        if (op == 0)
        {
            // sum
            ll l, r;
            cin >> l >> r;
            
            if(l > r) swap(l, r);
            ll result = query(r);
            if (l > 0)
                result -= query(l-1);
            cout << result << "\n";
        }
        else
        {
            // modify
            ll idx, target;
            cin >> idx >> target;
            ll diff = target - query(idx);
            if (idx > 0)
                diff += query(idx - 1);
            update(idx, diff);
        }
    }

    return 0;
}