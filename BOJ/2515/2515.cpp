#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

map<int, int, greater<int>> maxCost;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, s;
	cin >> n >> s;

	vector<pair<int, int>> drawing(n);

	for (int i = 0; i < n; ++i)
	{
		cin >> drawing[i].first >> drawing[i].second;
	}

	sort(drawing.begin(), drawing.end());

	maxCost[0] = 0;
	for (const auto [height, cost] : drawing)
	{
		auto target = maxCost.lower_bound(height - s);
		auto old = maxCost.lower_bound(height);
		if (target != maxCost.end())
		{
			maxCost[height] = max(old->second, target->second + cost);
		}
	}

	cout << maxCost.begin()->second << '\n';

	return 0;
}