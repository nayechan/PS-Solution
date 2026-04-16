#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int arr[1000];
int dp[1000][1000];

int get(int i, int j, bool turn)
{
	if (i > j) return 0;

	if (dp[i][j] == -1)
	{
		int a = get(i + 1, j, !turn) + turn * arr[i];
		int b = get(i, j - 1, !turn) + turn * arr[j];

		dp[i][j] = turn ? max(a, b) : min(a, b);
	}

	return dp[i][j];
}

void test()
{
	int n;
	cin >> n;

	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < n; ++i)
	{
		cin >> arr[i];
	}

	int result = get(0, n - 1, true);
	cout << result << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;

	for (int i = 0; i < t; ++i)
	{
		test();
	}
	return 0;
}