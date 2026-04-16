#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

long long sqDist(pair<int, int>& a, pair<int, int>& b)
{
	return 1LL * (a.first - b.first) * (a.first - b.first) +
		1LL * (a.second - b.second) * (a.second - b.second);
}

long long ccw(pair<int, int>& basis, pair<int, int>& a, pair<int, int>& b)
{
	return 1LL * (a.first - basis.first) * (b.second - basis.second)
		- 1LL * (a.second - basis.second) * (b.first - basis.first);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<pair<int, int>> points;

	for (int i = 0; i < n; ++i)
	{
		int px, py;
		char ch;

		cin >> px >> py >> ch;

		if (ch == 'Y')
			points.push_back({ px, py });
	}

	sort(points.begin(), points.end());

	pair<int, int> pivot = points[0];

	sort(points.begin() + 1, points.end(), [&pivot](pair<int, int>& a, pair<int, int>& b) {
		long long rotation = ccw(pivot, a, b);
		if (rotation != 0) return rotation > 0;

		long long distA = sqDist(a, pivot), distB = sqDist(b, pivot);
		return distA < distB;
		});

	auto lastItr = points.rbegin();
	while (lastItr + 1 != points.rend() && !ccw(pivot, *lastItr, *(lastItr + 1)))
		++lastItr;
	reverse(points.rbegin(), lastItr + 1);

	cout << points.size() << "\n";
	for (auto [px, py] : points)
	{
		cout << px << " " << py << "\n";
	}

	return 0;
}