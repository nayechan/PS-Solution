#include <iostream>
#include <vector>

using namespace std;

int main() {
	string input;
	cin >> input;

	int n = input.size();
	vector<vector<int>> dp(2, vector<int>(n + 1, 0));
	dp[1][0] = 1;

	for (int i = 1; i <= n; ++i)
	{
		for (int flag = 0; flag <= 1; ++flag)
		{
			if ((islower(input[i - 1])!=0) ^ flag)
			{
				dp[flag][i] = dp[flag][i - 1];
			}
			else
			{
				dp[flag][i] = min(dp[flag][i - 1] + 1, dp[!flag][i - 1] + 1);
			}
		}
	}

	int result = min(dp[0][n], dp[1][n]) + n;

	cout << result << endl;

	return 0;
}