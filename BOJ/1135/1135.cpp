#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void dfs(vector<vector<int>> &child, vector<int> &time, int current)
{
	for (const auto& e : child[current])
	{
		dfs(child, time, e);
	}

	int childCount = child[current].size();
	if (childCount == 0)
	{
		time[current] = 0;
		return;
	}

	sort(child[current].begin(), child[current].end(), [&time](int a, int b) {
		return time[a] > time[b];
		});


	time[current] = 0;
	for (int i = 0; i < childCount; ++i)
	{
		time[current] = max(time[current], time[child[current][i]] + i + 1);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<vector<int>> child(n);
	vector<int> time(n, 0);

	time[0] = 0;

	for (int i = 0; i < n; ++i)
	{
		int input;
		cin >> input;

		if (input != -1)
			child[input].push_back(i);
	}

	dfs(child, time, 0);

	cout << time[0] << '\n';

	return 0;
}