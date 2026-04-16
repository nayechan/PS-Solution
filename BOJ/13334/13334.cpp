#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

constexpr long long INF = 1012345678;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	auto comp = [](const pair<int, int>& a, pair<int, int>& b) {
		return a.first > b.first;
	};

	priority_queue<pair<int, int>, vector<pair<int,int>>, decltype(comp)> pq(comp);
	vector<pair<int, int>> data;
	for (int i = 0; i < n; ++i)
	{
		int s, e;
		cin >> s >> e;

		if (s > e) swap(s, e);

		data.push_back({ s,e });
	}

	sort(data.begin(), data.end(), [](const pair<int, int>& a, pair<int, int>& b) {
		return a.second < b.second;
	});

	int current = 0;

	int d;
	cin >> d;

	int result = 0;
	for (const auto [s, e] : data)
	{
		current = e;
		pq.push({ s,e });

		while (!pq.empty() && pq.top().first < e - d)
		{
			pq.pop();
		}

		int currentSize = pq.size();
		result = max(result, currentSize);
	}

	cout << result << "\n";

	


	return 0;
}