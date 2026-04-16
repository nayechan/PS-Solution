#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

long long ccw(pair<int,int> &basis, pair<int, int>& a, pair<int, int>& b)
{
	pair<int, int> v1 = {
		a.first - basis.first,
		a.second - basis.second
	};

	pair<int, int> v2 = {
		b.first - basis.first,
		b.second - basis.second
	};

	long long _ccw = ((long long)v1.first * v2.second - (long long)v1.second * v2.first);

	return _ccw;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<pair<int, int>> points(n);

	for (int i = 0; i < n; ++i)
	{
		cin >> points[i].first >> points[i].second;
	}

	sort(points.begin(), points.end());
	points.erase(unique(points.begin(), points.end()), points.end());

	pair<int, int> pivot = points[0];

	sort(points.begin() + 1, points.end(), [&pivot](pair<int, int>& a, pair<int, int>& b) {
		long long res = ccw(pivot, a, b);
		if (res != 0) return res > 0;

		long long distA = 1LL * (a.first - pivot.first) * (a.first - pivot.first);
		distA += 1LL * (a.second - pivot.second) * (a.second - pivot.second);

		long long distB = 1LL * (b.first - pivot.first) * (b.first - pivot.first);
		distB += 1LL * (b.second - pivot.second) * (b.second - pivot.second);

		return distA < distB;
		});

	auto lastItr = points.rbegin();

	/*
	while (lastItr+1 != points.rend() && !ccw(pivot, *lastItr, *(lastItr + 1)))
	{
		++lastItr;
	}

	reverse(points.rbegin(), lastItr+1);
	*/

	vector<pair<int, int>> ch;


	pair<int, int> prevV;

	for (int i = 0; i < points.size(); ++i)
	{

		while (ch.size() >= 2)
		{
			int count = ch.size();

			pair<int, int> p1 = ch[count - 2];
			pair<int, int> p2 = ch[count - 1];
			pair<int, int> p3 = points[i];

			//if (ccw(p1, p2, p3) < 0)
			if (ccw(p1, p2, p3) <= 0)
			{
				ch.pop_back();
			}
			else
			{
				break;
			}
		}

		ch.push_back(points[i]);

	}

	cout << ch.size() << '\n';


	return 0;
}