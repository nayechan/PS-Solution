#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int get(vector<vector<int>>& dp, vector<int>& male, vector<int>& female, int i, int j)
{
	if (dp[i][j] != -1)
	{
		return dp[i][j];
	}

	if (j == 0)
	{
		return 0;
	}

	if (i == j)
	{
		dp[i][j] = get(dp, male, female, i - 1, j - 1) + abs(male[i - 1] - female[j - 1]);
		return dp[i][j];
	}
	else if (i > j)
	{
		dp[i][j] = get(dp, male, female, i - 1, j - 1) + abs(male[i - 1] - female[j - 1]);
		dp[i][j] = min(dp[i][j], get(dp, male, female, i - 1, j));
		return dp[i][j];
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<int> male(n), female(m);

	for (int i = 0; i < n; ++i)
	{
		cin >> male[i];
	}

	for (int i = 0; i < m; ++i)
	{
		cin >> female[i];
	}

	if (n < m)
	{
		swap(n, m);
		swap(male, female);
	}

	sort(male.begin(), male.end());
	sort(female.begin(), female.end());

	vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

	int result = get(dp, male, female, n, m);
	cout << result << '\n';
	
	return 0;
}