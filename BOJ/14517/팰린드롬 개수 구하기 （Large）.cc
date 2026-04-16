#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int get(string& str, vector<vector<int>>& dp, int i, int j)
{
	int n = str.size();

	if (i < 0 || i >= n || j < 0 || j >= n || i > j) 
		return 0;

	if (dp[i][j] != -1)
		return dp[i][j];

	if (i == j)
	{
		dp[i][j] = 1;
	}
	else if (str[i] == str[j])
	{
		dp[i][j] = get(str, dp, i + 1, j) + get(str, dp, i, j - 1) + 1;
	}
	else
	{
		dp[i][j] = get(str, dp, i + 1, j) + get(str, dp, i, j - 1) - get(str, dp, i + 1, j - 1);
	}
	
	dp[i][j] = (dp[i][j] + 10007) % 10007;

	return dp[i][j];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	string s;
	cin >> s;

	int sz = s.size();

	vector<vector<int>> dp(sz, vector<int>(sz, -1));

	int count = 0;

	cout << get(s, dp, 0, sz - 1) << "\n";

	return 0;
}