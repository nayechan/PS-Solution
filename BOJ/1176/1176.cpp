#include <iostream>
#include <vector>

using namespace std;

long long get(vector<vector<long long>>& dp, vector<long long>& data, long long status, long long current, long long diff)
{
	if (dp[status][current] != -1) return dp[status][current];

	long long n = dp[0].size();
	if (status == (1 << n) - 1) return 1;

	long long result = 0;

	for (long long i = 0; i < n; ++i)
	{
		if (status & (1LL << i)) continue;
		if (abs(data[current] - data[i]) <= diff) continue;
		result += get(dp, data, status|(1LL<<i), i, diff);
	}

	dp[status][current] = result;
	return dp[status][current];
}

int main()
{
	long long n, k;
	cin >> n >> k;

	vector<long long> data(n);

	for (long long i = 0; i < n; ++i)
	{
		cin >> data[i];
	}

	vector<vector<long long>> dp(1LL << n, vector<long long>(n, -1));

	long long result = 0;
	for (long long i = 0; i < n; ++i)
	{
		result += get(dp, data, 1LL<<i, i, k);
	}

	cout << result << endl;

	return 0;
}