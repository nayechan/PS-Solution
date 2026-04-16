#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> pi;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int c, n;
	cin >> c >> n;

	vector<int> chicken(c);
	for (int i = 0; i < c; ++i)
	{
		int t;
		cin >> chicken[i];
	}
	sort(chicken.begin(), chicken.end());
	vector<pi> cow;
	for (int i = 0; i < n; ++i)
	{
		int a, b;
		cin >> a >> b;

		int l, r;
		l = lower_bound(chicken.begin(), chicken.end(), a) - chicken.begin();
		r = upper_bound(chicken.begin(), chicken.end(), b) - chicken.begin() - 1;

		if (l == c || r == -1)
		{
			// not found
			continue;
		}

		cow.push_back({ l,r });
	}

	sort(cow.begin(), cow.end(), [](const auto& a, const auto& b) {
		return a.first > b.first;
	});

	auto comp = [](pi& a, pi& b){
		return a.second > b.second;
	};

	priority_queue<pi, vector<pi>, decltype(comp)> pq(comp);

	int count = 0;

	for (int i = 0; i < c; ++i)
	{
		while (!cow.empty() && cow.back().first <= i)
		{
			pq.push(cow.back());
			cow.pop_back();
		}

		while (!pq.empty() && pq.top().second < i)
			pq.pop();


		if (!pq.empty())
		{
			pi top = pq.top();
			pq.pop();

			++count;
		}
	}

	cout << count << endl;

	return 0;
}