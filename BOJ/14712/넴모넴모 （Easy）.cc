#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <cassert>

using namespace std;

int get(vector<vector<vector<int>>>& dp, int i, int j, int m, int bit)
{
	if (j < 0)
	{
		--i;
		j = m - 1;
	}
	if (dp[i][j][bit] != -1) return dp[i][j][bit];

	if (j != 0)
	{
		bool isCurrent = bit & (1 << (m + 1));
		bool isLeft = bit & (1 << m);
		bool isTop = bit & 2;
		bool isTopLeft = bit & 1;

		if (isCurrent && isLeft && isTop && isTopLeft)
		{
			dp[i][j][bit] = 0;
			//cout << i << "/" << j << "/" << bit << " : " << 0 << endl;
			return 0;
		}
	}

	int result = 0;

	result += get(dp, i, j - 1, m, bit >> 1);
	result %= 1000000007;
	result += get(dp, i, j - 1, m, (1 << (m+1)) | (bit >> 1));
	result %= 1000000007;

	dp[i][j][bit] = result;
	//cout << i << "/" << j << "/" << bit << " : " << result << endl;

	return result;
}

int main()
{
	int n, m;
	cin >> n >> m;

	if (n < m) swap(n, m);

	vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(1 << (m + 2), -1)));

	int result = 0;

	for (int k = 0; k < (1 << (m+2)); ++k)
	{
		dp[0][0][k] = 0;
	}
	dp[0][0][0] = 1;
	dp[0][0][1] = 1;

	for (int i = 0; i < (1 << (m + 2)); ++i)
	{
		result += get(dp, n - 1, m - 1, m, i);
		result %= 1000000007;
	}

	cout << result << endl;

	return 0;
}