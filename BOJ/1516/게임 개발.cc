#include <iostream>
#include <vector>

using namespace std;

int get(vector<vector<int>>& edges, vector<int>& cost, vector<int>& dp, int i)
{
	if (dp[i] != -1)
		return dp[i];

	int result = 0;
	for (const auto& e : edges[i])
	{
		result = max(result, get(edges, cost, dp, e));
	}

	dp[i] = result + cost[i];

	return dp[i];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> cost(n);
	vector<int> dp(n, -1);
	vector<vector<int>> edges(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> cost[i];
		int input;
		while (true) {
			cin >> input;
			if (input == -1)
				break;
			edges[i].push_back(input-1);
		}
	}

	for (int i = 0; i < n; ++i)
	{
		get(edges, cost, dp, i);
	}

	for (const auto& e : dp)
	{
		cout << e << '\n';
	}
	return 0;
}