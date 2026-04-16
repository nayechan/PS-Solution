#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

long long sqDist(const pair<long long, long long>& a, const pair<long long, long long>& b)
{
	return 1LL * (a.first - b.first) * (a.first - b.first) + 1LL * (a.second - b.second) * (a.second - b.second);
}

long long ccw(const pair<long long, long long>& pivot, const pair<long long, long long>& a, const pair<long long, long long>& b)
{
	pair<long long, long long> lh = { a.first - pivot.first, a.second - pivot.second };
	pair<long long, long long> rh = { b.first - pivot.first, b.second - pivot.second };
	return (lh.first * rh.second - lh.second * rh.first);
}

void test()
{
	long long n;
	cin >> n;

	vector<pair<long long, pair<long long, long long>>> p(n);

	for (long long i = 0; i < n; ++i)
	{
		p[i].first = i;
		cin >> p[i].second.first >> p[i].second.second;
	}

	sort(p.begin(), p.end(), [](const pair<long long, pair<long long, long long>>& a, const pair<long long, pair<long long, long long>>& b) {
		if (a.second.second != b.second.second)
			return a.second.second < b.second.second;

		return a.second.first < b.second.first;
		});

	pair<long long, long long> pivot = p[0].second;
	sort(p.begin() + 1, p.end(), [&](const pair<long long, pair<long long, long long>>& a, const pair<long long, pair<long long, long long>>& b) {
		long long _ccw = ccw(pivot, a.second, b.second);

		if (_ccw != 0)
			return _ccw > 0;

		return sqDist(pivot, a.second) < sqDist(pivot, b.second);
		});

	long long i = n - 1;
	while (i > 0 && ccw(pivot, p[i].second, p[i - 1].second) == 0)
	{
		--i;
	}
	reverse(p.begin() + i, p.end());

	for (const auto& e : p)
	{
		cout << e.first << " ";
	}
	cout << "\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long c;
	cin >> c;

	for (long long i = 0; i < c; ++i)
	{
		test();
	}

	return 0;
}