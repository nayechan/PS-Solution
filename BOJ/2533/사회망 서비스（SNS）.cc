#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

constexpr long long INF = 1012345678;

void dfs(vector<vector<int>> &tree, vector<vector<int>> &dp, int v, int prev = -1)
{
	int accessCount = 0;
	for (const auto& v2 : tree[v])
	{
		if (v2 == prev) continue;
		++accessCount;
		dfs(tree, dp, v2, v);

		dp[0][v] += dp[1][v2];
		dp[1][v] += min(dp[0][v2], dp[1][v2]);
	}
	dp[1][v]++;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<vector<int>> tree(n);

	for (int i = 0; i < n - 1; ++i)
	{
		int a, b;
		cin >> a >> b;
		--a; --b;

		tree[a].push_back(b);
		tree[b].push_back(a);
	}

	vector<vector<int>> dp(2, vector<int>(n, 0));

	dfs(tree, dp, 0);

	cout << min(dp[0][0], dp[1][0]) << "\n";

	return 0;
}