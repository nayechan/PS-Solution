#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
using ll = long long;
constexpr ll INF = 1e18;

long long cross(const pair<int, int>& a, const pair<int, int>& b)
{
	return 1LL * a.first * b.second - 1LL * a.second * b.first;
}

long long ccw(const pair<int, int> &pivot, const pair<int, int> &p1, const pair<int, int> &p2)
{
	pair<int, int> v1 = { p1.first - pivot.first, p1.second - pivot.second };
	pair<int, int> v2 = { p2.first - pivot.first, p2.second - pivot.second };

	return cross(v1, v2);
}

long long dist(const pair<int, int>& a, const pair<int, int>& b)
{
	return 1LL * (a.first - b.first) * (a.first - b.first) +
		1ll* (a.second - b.second)* (a.second - b.second);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	if (n < 3)
	{
		cout << 0 << "\n";
		return 0;
	}

	vector<pair<int, int>> points(n);

	for (int i = 0; i < n; ++i)
	{
		cin >> points[i].first >> points[i].second;
	}

	sort(points.begin(), points.end());

	pair<int, int> pivot = points[0];

	sort(points.begin() + 1, points.end(), [&pivot](const pair<int, int>& a, const pair<int, int>& b) {
		long long res = ccw(pivot, a, b);

		if (res != 0) {
			return res > 0;
		}

		return dist(pivot, a) < dist(pivot, b);
		});

	vector<pair<int, int>> ch;

	for (int i = 0; i < n; ++i)
	{
		while (ch.size() >= 2)
		{
			ll _ccw = ccw(
				ch[ch.size() - 2], ch[ch.size() - 1], points[i]
			);

			if (_ccw <= 0)
				ch.pop_back();
			else
				break;
		}

		ch.push_back(points[i]);
	}

	int chSize = ch.size();

	long long result = 0;

	pivot = ch[0];

	for (int i = 1; i < chSize - 1; ++i)
	{
		pair<int, int> v1 = { ch[i].first - pivot.first, ch[i].second - pivot.second };
		pair<int, int> v2 = { ch[i+1].first - pivot.first, ch[i+1].second - pivot.second };

		long long _cross = cross(v1, v2);
		result += _cross;
	}

	cout << result / 100 << "\n";

	return 0;
}