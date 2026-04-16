#include <iostream>
#include <vector>
#include <climits>

using namespace std;

template<typename T>
using vv = vector<vector<T>>;

typedef unsigned long long ull;

ull get(vv<ull> &dp, ull k, ull n)
{
	if (dp[k][n] != ULLONG_MAX)
		return dp[k][n];

	if (k <= 0)
		return 0;

	if (n <= 0)
		return 1;

	dp[k][n] = get(dp, k - 1, n - 1) + get(dp, k + 1, n - 1);
	return dp[k][n];
}

int main()
{
	ull k, n;
	cin >> k >> n;

	vv<ull> dp(k + n + 1, vector<ull>(n + 1, ULLONG_MAX));

	ull result = get(dp, k, n);
	cout << result << endl;

	return 0;
}