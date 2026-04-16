#include <iostream>

#include <vector>

using namespace std;

long long get(vector<vector<long long>>& data, vector<vector<long long>>& dp, long long i, long long j, long long n)
{
	if (i >= n || j >= n) return 0;
	if (i == n - 1 && j == n - 1) return 1;
	if (data[i][j] == 0) return 0;

	if (dp[i][j] == -1)
		dp[i][j] = get(data, dp, i + data[i][j], j, n) + get(data, dp, i, j + data[i][j], n);

	return dp[i][j];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n;
	cin >> n;

	vector<vector<long long>> data(n, vector<long long>(n)), dp(n, vector<long long>(n, -1));

	for (long long i = 0; i < n; ++i)
	{
		for (long long j = 0; j < n; ++j)
		{
			cin >> data[i][j];
		}
	}

	cout << get(data, dp, 0, 0, n) << '\n';

	return 0;
}