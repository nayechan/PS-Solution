#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	int min;
	cin >> min;

	int m = min;

	vector<int> data(min, -1);

	for (int i = 1; i < n; ++i)
	{
		int num;
		cin >> num;

		if (num < min)
		{
			for (int i = num; i < min; ++i)
			{
				data[i] = i % num;
			}
			min = num;
		}
	}

	long long sum = 0;
	vector<int> dp(m, 0);
	for (int i = 0; i < m; ++i)
	{
		if (data[i] == -1)
			dp[i] = i;

		else dp[i] = dp[data[i]];

		sum += dp[i];
	}

	long double result = sum;
	result /= (long double)m;
	cout << setprecision(12) << fixed << result << endl;
	
	return 0;
}