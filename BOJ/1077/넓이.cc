#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
using ll = long long;
using ld = long double;
constexpr ll INF = 1e18;

ld cross_ld(const pair<ld, ld>& a, const pair <ld, ld>& b)
{
	return 1.0l * a.first * b.second - 1.0l * a.second * b.first;
}

long long cross(const pair<int, int>& a, const pair<int, int>& b)
{
	return 1LL * a.first * b.second - 1LL * a.second * b.first;
}

ld ccw_ld(const pair<ld, ld>& pivot, const pair<ld, ld>& p1, const pair<ld, ld>& p2)
{
	pair<ld, ld> v1 = { p1.first - pivot.first, p1.second - pivot.second };
	pair<ld, ld> v2 = { p2.first - pivot.first, p2.second - pivot.second };

	return cross_ld(v1, v2);
}

long long ccw(const pair<int, int>& pivot, const pair<int, int>& p1, const pair<int, int>& p2)
{
	pair<int, int> v1 = { p1.first - pivot.first, p1.second - pivot.second };
	pair<int, int> v2 = { p2.first - pivot.first, p2.second - pivot.second };

	return cross(v1, v2);
}

ld dist_ld(const pair<ld, ld>& a, const pair<ld, ld>& b)
{
	return 1.0l * (a.first - b.first) * (a.first - b.first) +
		1.0l * (a.second - b.second) * (a.second - b.second);
}

long long dist(const pair<int, int>& a, const pair<int, int>& b)
{
	return 1LL * (a.first - b.first) * (a.first - b.first) +
		1ll * (a.second - b.second) * (a.second - b.second);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	if (n < 3 || m < 3)
	{
		cout << 0 << "\n";
		return 0;
	}

	vector<pair<int, int>> a(n), b(m);

	for (int i = 0; i < n; ++i)
	{
		cin >> a[i].first >> a[i].second;
	}

	for (int i = 0; i < m; ++i)
	{
		cin >> b[i].first >> b[i].second;
	}

	vector<pair<ld, ld>> points;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			pair<int, int> a1 = a[i], a2 = a[(i + 1) % n];
			pair<int, int> b1 = b[j], b2 = b[(j + 1) % m];

			long long ccw1 = ccw(a1, a2, b1);
			long long ccw2 = ccw(a1, a2, b2);
			long long ccw3 = ccw(b1, b2, a1);
			long long ccw4 = ccw(b1, b2, a2);

			if (ccw1 * ccw2 <= 0 && ccw3 * ccw4 <= 0)
			{
				long long det = ccw1 - ccw2;
				if (det != 0)
				{
					ld ratio = 1.0l * (ld)abs(ccw1) / ((ld)abs(ccw1) + (ld)abs(ccw2));
					ld intersectX = b1.first + (b2.first - b1.first) * ratio;
					ld intersectY = b1.second + (b2.second - b1.second) * ratio;

					points.push_back({ intersectX, intersectY });
				}
			}
		}
	}

	for (int i = 0; i < m; ++i)
	{
		bool isInside = true;
		for (int j = 0; j < n; ++j)
		{
			if (ccw(a[j], a[(j + 1) % n], b[i]) < 0)
			{
				isInside = false;
				break;
			}
		}

		if (isInside)
		{
			points.push_back(b[i]);
		}
	}

	for (int i = 0; i < n; ++i)
	{
		bool isInside = true;
		for (int j = 0; j < m; ++j)
		{
			if (ccw(b[j], b[(j + 1) % m], a[i]) < 0)
			{
				isInside = false;
				break;
			}
		}

		if (isInside)
		{
			points.push_back(a[i]);
		}
	}

	sort(points.begin(), points.end());
	points.erase(unique(points.begin(), points.end(),
		[](const pair<ld, ld>& a, const pair<ld, ld>& b) {
			return abs(a.first - b.first) < 1e-12 && abs(a.second - b.second) < 1e-12;
		}), points.end());

	if (points.size() > 0)
	{
		pair<ld, ld> pivot = points[0];

		sort(points.begin() + 1, points.end(),
			[&pivot](const pair<ld, ld>& a, const pair<ld, ld>& b) {
				ld res = ccw_ld(pivot, a, b);

				if (abs(res) > 1e-12) {
					return res > 0;
				}

				return dist_ld(pivot, a) < dist_ld(pivot, b);
			});
	}

	if (points.size() < 3)
	{
		cout << 0 << "\n";
		return 0;
	}

	pair<ld, ld> pivot = points[0];

	vector<pair<ld, ld>> ch;
	for (int i = 0; i < points.size(); ++i)
	{
		while (ch.size() >= 2)
		{
			int count = ch.size();

			pair<ld, ld> p1 = ch[count - 2];
			pair<ld, ld> p2 = ch[count - 1];
			pair<ld, ld> p3 = points[i];

			ld _ccw = ccw_ld(p1, p2, p3);

			if (_ccw < 1e-12)
				ch.pop_back();
			else
				break;
		}
		ch.push_back(points[i]);
	}

	int chSize = ch.size();
	long double result = 0;

	pivot = ch[0];

	for (int i = 1; i < chSize - 1; ++i)
	{
		pair<ld, ld> v1 = { ch[i].first - pivot.first, ch[i].second - pivot.second };
		pair<ld, ld> v2 = { ch[i + 1].first - pivot.first, ch[i + 1].second - pivot.second };

		ld _cross = cross_ld(v1, v2);
		result += _cross;
	}

	cout.precision(15);
	cout << fixed << abs(result) / 2.0l << "\n";

	return 0;
}