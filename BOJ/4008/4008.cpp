
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

using ll = long long;
using ld = long double;

bool bad(pair<ll, ll>& l1, pair<ll, ll>& l2, pair<ll, ll>& l3)
{
	return 1.0l * (l2.second - l1.second) * (l2.first - l3.first)
		>= 1.0l * (l3.second - l2.second) * (l1.first - l2.first);
}

ll query(vector<pair<ll, ll>>& f, ll x)
{
	ll l = 0, r = f.size() - 1;

	while (l < r)
	{
		ll mid = (l + r) >> 1;
		if (1.0l * f[mid].first * x + f[mid].second 
			>= 1.0l * f[mid + 1].first * x + f[mid + 1].second)
			r = mid;
		else
			l = mid + 1;
	}

	return llroundl(1.0l * f[l].first * x + f[l].second);
}

void addLine(vector<pair<ll, ll>>& f, pair<ll, ll> line)
{
	while (f.size() >= 2 && bad(f[f.size() - 2], f.back(), line))
	{
		f.pop_back();
	}

	f.push_back(line);
}

ll getSlope(vector<ll>& s, ll a, ll b, ll j)
{
	return -2 * a * s[j] + b;
}

ll getSection(vector<ll>& s, ll a, ll b, ll c, ll j)
{
	return a * s[j] * s[j] - b * s[j] + c;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ll n;
	cin >> n;

	ll a, b, c;
	cin >> a >> b >> c;

	vector<ll> str(n);
	for (ll i = 0; i < n; ++i)
	{
		cin >> str[i];
	}

	vector<ll> s(n + 1);
	s[0] = 0;
	for (ll i = 0; i < n; ++i)
	{
		s[i + 1] = s[i] + str[i];
	}

	vector<pair<ll, ll>> f;
	vector<ll> dp(n + 1, 0);
	dp[0] = 0;
	f.push_back({ getSlope(s, a, b, 0), getSection(s, a, b, c, 0) + dp[0] });
	for (ll i = 1; i <= n; ++i)
	{
		dp[i] = query(f, s[i]) + a * s[i] * s[i];
		addLine(f, { getSlope(s, a, b, i), getSection(s, a, b, c, i) + dp[i] });
	}

	ll result = dp[n];

	cout << result << "\n";

	return 0;
}