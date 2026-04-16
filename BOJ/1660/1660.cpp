#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <climits>

using namespace std;

long long get(vector<long long>& dp, vector <long long> & num, long long k)
{
	if (k < 0) return LLONG_MAX;
	if (dp[k] != -1) return dp[k];

	long long _min = LLONG_MAX;
	for (long long i = 0; num[i] <= k; ++i)
	{
		_min = min(_min, get(dp, num, k - num[i]) + 1);
	}
	dp[k] = _min;
	return dp[k];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	long long n;

	cin >> n;

	if (n == 1)
	{
		cout << 1 << endl;
		return 0;
	}

	vector<long long> num(n);
	iota(num.begin(), num.end(), 1);

	for (long long i = 1; i < n; ++i)
	{
		num[i] = num[i] + num[i - 1];
	}

	for (long long i = 1; i < n; ++i)
	{
		num[i] = num[i] + num[i - 1];
	}

	long long result = 0;
	for (result = 0; result < n; ++result)
	{
		//cout << num[result] << " ";
		if (num[result] > n) break;
	}

	long long final = 0;

	vector<long long> dp(n + 1, -1);
	dp[0] = 0;

	final = get(dp, num, n);

	cout << final << endl;


	return 0;
}