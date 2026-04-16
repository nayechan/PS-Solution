#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>

using ll = long long;

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ll n, q;
	cin >> n >> q;

	vector<ll> data(n+1, 0LL);

	for (int i = 0; i < q; ++i)
	{
		ll op, a, b;
		cin >> op >> a >> b;

		if (op == 1)
		{
			while (a < data.size()) {
				data[a] += b;
				a += (a & -a);
			}
		}
		else
		{
			ll result = 0;
			--a;
			while (b > 0) {
				result += data[b];
				b &= (b - 1);
			}
			while (a > 0) {
				result -= data[a];
				a &= (a - 1);
			}
			cout << result << '\n';
		}
	}

	return 0;
}