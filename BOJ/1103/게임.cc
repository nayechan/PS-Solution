#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

template <typename T>
using vv = vector<vector<T>>;

constexpr int dx[] = { -1, 1, 0, 0 };
constexpr int dy[] = { 0, 0, -1, 1 };

int get(vv<int>& board, vv<int>& dp, vv<bool>& visited, int i, int j)
{
	int n = board.size();
	int m = board[0].size();

	if (i < 0 || j < 0 || i >= n || j >= m)
	{
		return 0;
	}

	if (dp[i][j] != -1)
	{
		return dp[i][j];
	}

	if (visited[i][j])
	{
		dp[i][j] = INT_MAX;
		return INT_MAX;
	}

	int dist = board[i][j];

	if (dist == 0)
	{
		dp[i][j] = 0;
		return 0;
	}

	visited[i][j] = true;


	vector<int> result;

	for (int c = 0; c < 4; ++c)
	{
		int _result = get(board, dp, visited, i + dist * dx[c], j + dist * dy[c]);

		if (_result == INT_MAX)
			result.push_back(INT_MAX);

		else
			result.push_back(_result+1);
	}


	visited[i][j] = false;

	dp[i][j] = *max_element(result.begin(), result.end());

	return dp[i][j];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;
	vv<int> board(n, vector<int>(m));
	vv<int> dp(n, vector<int>(m, -1));
	vv<bool> visited(n, vector<bool>(m, false));

	for (int i = 0; i < n; ++i)
	{
		string input;
		cin >> input;

		int j = 0;
		for (const char& ch : input)
		{
			if (ch == 'H')
			{
				board[i][j] = 0;
			}
			else
			{
				board[i][j] = ch - '0';
			}

			++j;
		}
	}

	int result = get(board, dp, visited, 0, 0);

	if (result == INT_MAX)
		cout << -1 << endl;
	else
		cout << result << endl;

	return 0;
}