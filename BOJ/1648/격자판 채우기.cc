#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <set>

using namespace std;

int get(vector<vector<int>>& dp, int status, int idx, int n, int m)
{
	int r = idx / m, c = idx % m;

	//cout << status << " " << r << " " << c << endl;

	bool isCurrent = status & 1;
	bool isLeft = (status >> 1) & 1;
	bool isUp = (status >> m) & 1;

	int total = 0;

	if (idx == -1)
		return 1;

	if (idx < 0)
		return 0;

	if (dp[status][idx] != -1)
		return dp[status][idx];

	if (isLeft && isCurrent && c >= 1)
	{
		int newStatus = (status >> 2);
		newStatus |= (1 << (m - 1));
		newStatus |= (1 << m);
		total += get(dp, newStatus, idx - 2, n, m);
		total %= 9901;
	}

	if (isUp && isCurrent && r >= 1)
	{
		int newStatus = (status ^ (1 << m));
		newStatus >>= 1;
		newStatus |= (1 << m);
		total += get(dp, newStatus, idx-1, n, m);
		total %= 9901;
	}

	if (!isCurrent)
	{
		int newStatus = (status >> 1);
		newStatus |= (1 << m);

		total += get(dp, newStatus, idx-1, n, m);
		total %= 9901;
	}

	total %= 9901;
	dp[status][idx] = total;
	return total;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> dp((1<<(m+1)), vector<int>(n * m, -1));

	cout << get(dp, (1 << (m+1)) - 1, n*m - 1, n, m) % 9901 << "\n";

	return 0;
}