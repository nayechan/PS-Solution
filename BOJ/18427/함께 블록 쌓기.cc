#include <iostream>
#include <array>
#include <vector>
#include <sstream>
#include <cstring>

using namespace std;

int f(vector<vector<int>>& data, array<array<int, 1001>, 51>& dp, int n, int h)
{
	if (h == 0) return 1;
	if (h < 0) return 0;
	if (n <= 0) return 0;

	if (dp[n][h] != -1) return dp[n][h];

	int sum = 0;

	sum += f(data, dp, n - 1, h);
	for (const auto& i : data[n - 1])
	{
		sum += f(data, dp, n - 1, h - i);
	}

	sum %= 10007;
	dp[n][h] = sum;
	return sum;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m, h;

	cin >> n >> m >> h;

	vector<vector<int>> per(n, vector<int>());
	array<array<int, 1001>, 51> dp;
	memset(dp.data(), -1, sizeof(dp));

	cin.ignore();

	for(int i=0;i<n;++i)
	{
		string str;
		getline(cin, str);

		stringstream ss(str);
		int input;

		while (ss >> input)
		{
			per[i].push_back(input);
		}
	}

	int result = f(per, dp, n, h);
	cout << result << endl;
	return 0;
}