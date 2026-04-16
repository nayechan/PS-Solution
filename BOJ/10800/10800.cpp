#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main()
{
	int n;
	cin >> n;

	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	vector<int> color(n);
	vector<int> size(n);
	vector<vector<int>> data(n);
	vector<vector<int>> sum(n);

	vector<int> allData;
	vector<int> allSum;

	for (int i = 0; i < n; ++i)
	{
		cin >> color[i] >> size[i];
		--color[i];

		data[color[i]].push_back(size[i]);
		allData.push_back(size[i]);
	}

	for (int i = 0; i < n; ++i)
	{
		sort(data[i].begin(), data[i].end());
		int count = data[i].size();
		int prev = 0;
		for (int j = 0; j < count; ++j)
		{
			sum[i].push_back(data[i][j] + prev);
			prev += data[i][j];
		}
	}

	{
		sort(allData.begin(), allData.end());
		int count = allData.size();
		int prev = 0;
		for (int i = 0; i < count; ++i)
		{
			allSum.push_back(allData[i] + prev);
			prev += allData[i];
		}
	}

	for (int i = 0; i < n; ++i)
	{
		int _color = color[i];
		int _size = size[i];

		int totalSum = 0;

		auto itr = lower_bound(allData.begin(), allData.end(), _size);
		if (itr != allData.begin())
		{
			int index = itr - allData.begin() - 1;
			totalSum += allSum[index];
		}

		itr = lower_bound(data[_color].begin(), data[_color].end(), _size);
		if (itr != data[_color].begin())
		{
			int index = itr - data[_color].begin() - 1;
			totalSum -= sum[_color][index];
		}

		cout << totalSum << '\n';
	}
	return 0;
}