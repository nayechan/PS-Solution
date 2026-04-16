#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <set>

using namespace std;

int cost[4][4] = {
	{100, 70, 40, 0},
	{70, 50, 30, 0},
	{40, 30, 20, 0},
	{0, 0, 0, 0}
};

int get(vector<vector<int>>& dp, vector<vector<int>> &board, int status, int idx, int n, int m)
{
	int r = idx / m, c = idx % m;

	//cout << status << " " << r << " " << c << endl;

	bool isCurrent = status & 1;
	bool isLeft = (status >> 1) & 1;
	bool isUp = (status >> m) & 1;

	int result = 0;

	if (idx == -1)
		return 0;

	if (idx < 0)
		return 0;

	if (dp[status][idx] != -1)
		return dp[status][idx];

	int newStatus;
	if (isLeft && isCurrent && c >= 1)
	{
		newStatus = (status >> 2);
		newStatus |= (1 << (m - 1));
		newStatus |= (1 << m);

		int price = cost[board[r][c]][board[r][c - 1]];

		result = max(result, get(dp, board, newStatus, idx - 2, n, m) + price);
	}

	if (isUp && isCurrent && r >= 1)
	{
		newStatus = (status ^ (1 << m));
		newStatus >>= 1;
		newStatus |= (1 << m);

		int price = cost[board[r][c]][board[r - 1][c]];

		result = max(result, get(dp, board, newStatus, idx - 1, n, m) + price);
	}

	newStatus = (status >> 1);
	newStatus |= (1 << m);

	result = max(result, get(dp, board, newStatus, idx - 1, n, m));

	dp[status][idx] = result;
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<vector<int>> dp((1 << (n + 1)), vector<int>(n * n, -1));

	vector<vector<int>> board(n, vector<int>(n));

	for (int i = 0; i < n; ++i)
	{
		string str; cin >> str;
		for (int j = 0; j < n; ++j)
		{
			int ch = str[j];

			ch -= 'A';

			if (ch > 3) ch = 3;

			board[i][j] = ch;
		}
	}

	cout << get(dp, board, (1 << (n + 1)) - 1, n * n - 1, n, n) << "\n";

	return 0;
}