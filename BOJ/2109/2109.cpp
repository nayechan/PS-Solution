#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using pii = pair<int, int>;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	int maxD = 0;

	vector<pii> data(n);

	for (int i = 0; i < n; ++i)
	{
		cin >> data[i].second >> data[i].first;

		maxD = max(maxD, data[i].first);
	}

	sort(data.begin(), data.end(), [](const pii& a, const pii& b) {
		if (a.first == b.first)
		{
			return a.second < b.second;
		}

		return a.first < b.first;
	});

	auto comp = [](const pii& a, const pii& b) {
		return a.second < b.second;
	};

	priority_queue<pii, vector<pii>, decltype(comp)> pq(comp);

	int result = 0;

	for (int i = maxD; i >= 1; --i)
	{
		while (!data.empty() && data.back().first >= i)
		{
			pq.push(data.back());
			data.pop_back();
		}

		if (!pq.empty())
		{
			result += pq.top().second;
			pq.pop();
		}
	}

	cout << result << endl;
	return 0;
}