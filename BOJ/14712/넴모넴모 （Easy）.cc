#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <cassert>
#include <cstring>

using namespace std;

int dp[1048576], tmp[1048576];

int get(int i, int j, int m, int bit)
{
	if (j != 0)
	{
		bool isCurrent = bit & (1 << (m + 1));
		bool isLeft = bit & (1 << m);
		bool isTop = bit & 2;
		bool isTopLeft = bit & 1;

		if (isCurrent && isLeft && isTop && isTopLeft)
		{
			tmp[bit] = 0;
			//cout << i << "/" << j << "/" << bit << " : " << 0 << endl;
			return 0;
		}
	}

	int result = 0;

	result += dp[bit>>1];
	result %= 1000000007;
	result += dp[(1 << (m + 1)) | (bit >> 1)];
	result %= 1000000007;

	tmp[bit] = result;

	return result;
}

int main()
{
	int n, m;
	cin >> n >> m;

	if (n < m) swap(n, m);

	memset(dp, 0, sizeof(dp));

	dp[0] = 1;
	dp[1] = 1;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (i == 0 && j == 0) continue;
			memset(tmp, -1, sizeof(tmp));
			for (int k = 0; k < (1 << (m + 2)); ++k)
			{
				get(i, j, m, k);
			}
			memcpy(dp, tmp, sizeof(tmp));
		}
	}

	int result = 0;

	for (int i = 0; i < (1 << (m + 2)); ++i)
	{
		result += dp[i];
		result %= 1000000007;
	}

	cout << result << endl;

	return 0;
}