#include <iostream>
#include <vector>

using namespace std;

long long get(vector<vector<long long>>& dp, int n, int h)
{
	long long result = 0;

	if (dp[n][h] != -1)
		return dp[n][h];

	if (n > 0)
		result += get(dp, n - 1, h + 1);
	if (h > 0)
		result += get(dp, n, h - 1);

	dp[n][h] = result;
	return result;
}

int main()
{
	vector<vector<long long>> dp(61, vector<long long>(61, -1));
	dp[0][0] = 1;

	while(true)
	{
		int input;
		cin >> input;

		if (input == 0) break;

		cout << get(dp, input, 0) << endl;
	}
	return 0;
}