#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const vector<int> dx = { 0, 0, 1, -1 };
const vector<int> dy = { 1, -1, 0, 0 };

int f(vector<vector<int>>& data, vector<vector<int>>& dp, int i, int j)
{
	int n = dp.size();
	if (i < 0 || j < 0 || i >= n || j >= n) return -1;

	if (dp[i][j] == -1)
	{
		dp[i][j] = 0;
		for (int d = 0; d < 4; ++d)
		{
			int nextI = i + dx[d];
			int nextJ = j + dy[d];

			if (nextI >= 0 && nextI < n && nextJ >= 0 && nextJ < n && data[nextI][nextJ] > data[i][j])
			{

				dp[i][j] = max(dp[i][j], f(data, dp, i + dx[d], j + dy[d]) + 1);
			}
		}
	}

	return dp[i][j];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<vector<int>> data(n, vector<int>(n));
	vector<vector<int>> dp(n, vector<int>(n, -1));

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> data[i][j];
		}
	}

	int result = -1;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			result = max(result, f(data, dp, i, j));
		}
	}

	cout << result + 1 << endl;
	return 0;
}