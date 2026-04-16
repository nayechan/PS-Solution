#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int d, n;
	cin >> d >> n;

	vector<int> temp(d);
	vector<int> cloth(n);
	vector<int> minTemp(n);
	vector<int> maxTemp(n);

	for(int i=0;i<d;++i)
	{
		cin >> temp[i];
	}
	for (int i = 0; i < n; ++i)
	{
		cin >> minTemp[i] >> maxTemp[i] >> cloth[i];
	}

	vector<vector<int>> dp(d, vector<int>(n, -1));
	for (int i = 0; i < n; ++i)
	{
		if (minTemp[i] > temp[0] || temp[0] > maxTemp[i]) continue;
		for (int j = 0; j < n; ++j)
		{
			if (minTemp[j] > temp[1] || temp[1] > maxTemp[j]) continue;
			dp[0][j] = max(dp[0][j], abs(cloth[i] - cloth[j]));
		}
	}

	for (int i = 1; i < d - 1; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (minTemp[j] > temp[i+1] || temp[i+1] > maxTemp[j]) continue;

			for (int k = 0; k < n; ++k)
			{
				if (dp[i-1][k] == -1) continue;

				int localV = abs(cloth[k] - cloth[j]) + dp[i-1][k];
				dp[i][j] = max(dp[i][j], localV);
			}
		}
	}

	cout << *max_element(dp[d-2].begin(), dp[d-2].end()) << endl;

	return 0;
}