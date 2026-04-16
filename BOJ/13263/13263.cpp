#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;
using ld = long double;

pair<ld, ld> getIntersect(pair<ld, ld>& l1, pair<ld, ld>& l2)
{
	return { l2.second - l1.second, l1.first - l2.first };
}

bool bad(pair<ld, ld>& l1, pair<ld, ld>& l2, pair<ld, ld>& l3)
{
	pair<ld, ld> fracA = getIntersect(l1, l2);
	pair<ld, ld> fracB = getIntersect(l2, l3);

	return fracA.first * fracB.second >= fracA.second * fracB.first;
}

ll query(vector<pair<ld, ld>> &f, ll x)
{
	int l = 0, r = f.size() - 1;

	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (f[mid].first * x + f[mid].second <= f[mid + 1].first * x + f[mid + 1].second)
			r = mid;
		else
			l = mid + 1;
	}

	return f[l].first * x + f[l].second;
}

void addLine(vector<pair<ld, ld>>& f, pair<ld, ld> line)
{
	while (f.size() >= 2 && bad(f[f.size()-2], f.back(), line))
	{
		f.pop_back();
	}

	f.push_back(line);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ll n;
	cin >> n;

	vector<ll> a(n), b(n);
	for (ll i = 0; i < n; ++i)
	{
		cin >> a[i];
	}
	for (ll i = 0; i < n; ++i)
	{
		cin >> b[i];
	}
	vector<pair<ld, ld>> f;
	vector<ll> dp(n, 0);
	dp[0] = 0;
	f.push_back({ b[0], dp[0]});
	for (ll i = 1; i < n; ++i)
	{
		dp[i] = query(f, a[i]);
		addLine(f, { b[i], dp[i]});
	}

	ll result = dp[n - 1];

	cout << result << "\n";


	return 0;
}