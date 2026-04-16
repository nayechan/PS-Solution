#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
	int n;
	cin >> n;

	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	vector<pair<int, int>> data(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> data[i].first >> data[i].second;
	}
	sort(data.begin(), data.end(),
		[](const pair<int, int>& a, const pair<int, int>& b) {
			return a.first < b.first;
		}
	);

	auto comp = [](const pair<int, int>& a, const pair<int, int>& b) {
		return a.second < b.second;
	};

	int total = 0;
	priority_queue<pair<int, int>, vector<pair<int,int>>, decltype(comp)> pq(comp);
	for (int i = n; i >= 1; --i)
	{
		while (!data.empty() && data.back().first >= i)
		{
			pq.push(data.back());
			data.pop_back();
		}

		if (!pq.empty())
		{
			pair<int, int> result = pq.top();
			//cout << i << "|" << result.first << "/" << result.second << endl;
			total += result.second;
			pq.pop();
		}
	}

	cout << total << endl;

	return 0;
}