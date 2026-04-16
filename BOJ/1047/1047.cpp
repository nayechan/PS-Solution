#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

pair<int,int> simulate(vector<pair<int, int>>& data, vector<int>& cost, int x1, int x2, int y1, int y2, int length)
{
	int count = 0;
	int costSum = 0;

	int index = 0;

	vector<int> sortedInnerExclusive;
	for (const auto& [x, y] : data)
	{
		if (x < x1 || x > x2 || y < y1 || y > y2)
		{
			++count;
			costSum += cost[index];
		}
		else if (x != x1 && x != x2 && y != y1 && y != y2)
		{
			sortedInnerExclusive.push_back(index);
		}
		++index;
	}

	sort(sortedInnerExclusive.begin(), sortedInnerExclusive.end(), [&cost](const int& a, const int& b) {
		return cost[a] < cost[b];
	});

	while (length > costSum && sortedInnerExclusive.size() > 0)
	{
		costSum += cost[sortedInnerExclusive.back()];
		++count;
		sortedInnerExclusive.pop_back();
	}

	return { count, costSum };
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<int> bx(n), by(n);
	vector<pair<int, int>> data(n);
	vector<int> cost(n);

	for (int i = 0; i < n; ++i)
	{
		int x, y, c;
		cin >> x >> y >> c;

		bx[i] = x;
		by[i] = y;

		data[i] = { x,y };
		cost[i] = c;
	}

	sort(bx.begin(), bx.end());
	sort(by.begin(), by.end());

	int result = 987654321;

	for (int dx1 = 0; dx1 < n; ++dx1)
	{
		for (int dx2 = dx1; dx2 < n; ++dx2)
		{
			for (int dy1 = 0; dy1 < n; ++dy1)
			{
				for (int dy2 = dy1; dy2 < n; ++dy2)
				{
					int length = 2 * (bx[dx2] - bx[dx1] + by[dy2] - by[dy1]);

					auto [count, costSum] = simulate(data, cost, bx[dx1], bx[dx2], by[dy1], by[dy2], length);
					if (costSum >= length)
					{
						result = min(result, count);
					}
				}
			}
		}
	}

	cout << result << '\n';
}