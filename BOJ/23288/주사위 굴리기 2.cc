#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
#include <queue>

using namespace std;

constexpr int INF = 987654321;
constexpr int BOTTOM = 0, SOUTH = 1, EAST = 2;

constexpr pair<int, int> delta[4] = {
	{0,1},{1,0},{0,-1},{-1,0}
};

// 1 = cw, -1 = ccw
void rotate(pair<int, int>& direction, int v)
{
	auto& [dx, dy] = direction;

	direction = { dy * -v, dx * v };
}

void roll(tuple<int, int, int>& dice, pair<int, int>& direction)
{
	auto& [dx, dy] = direction;
	auto& [b, s, e] = dice;

	if (dx != 0)
	{

		int tmp = b;
		b = (7 + dx * e) % 7; // e or 7 - e
		e = (7 - dx * tmp) % 7; // 7 - tmp or tmp
	}
	if (dy != 0)
	{

		int tmp = b;
		b = (7 + dy * s) % 7;
		s = (7 - dy * tmp) % 7;
	}
}

void bfs(vector<vector<int>>& board, vector<vector<int>>& score, vector<vector<bool>>& visited, pair<int,int> pos)
{
	auto& [x, y] = pos;
	int n = board.size();
	int m = board[0].size();

	queue<pair<int, int>> q;
	vector<pair<int, int>> result;

	q.push(pos);
	visited[x][y] = true;

	while (!q.empty())
	{
		auto [cx, cy] = q.front();
		result.push_back({ cx, cy });

		q.pop();

		for (const auto& [dx, dy] : delta)
		{
			if (0 <= cx + dx && cx + dx < n && 0 <= cy + dy && cy + dy < m 
				&& board[cx+dx][cy+dy] == board[cx][cy] && !visited[cx+dx][cy+dy])
			{
				q.push({ cx + dx, cy + dy });
				visited[cx + dx][cy + dy] = true;
			}
		}
	}

	int count = result.size();

	for (const auto& [cx, cy] : result)
	{
		score[cx][cy] = count * board[cx][cy];
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m, k;
	cin >> n >> m >> k;

	tuple<int, int, int> dice = { 6,5,3 };
	pair<int, int> direction = { 1, 0 };
	pair<int, int> pos = { 0,0 };

	vector<vector<int>> board(n, vector<int>(m));
	vector<vector<int>> score(n, vector<int>(m));
	vector<vector<bool>> visited(n, vector<bool>(m, false));

	int finalResult = 0;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cin >> board[i][j];
		}
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if(!visited[i][j])
				bfs(board, score, visited, { i,j });
		}
	}

	while (k--)
	{
		auto& [r, c] = pos;
		auto& [dx, dy] = direction;

		if (r + dy < 0 || r + dy >= n || c + dx < 0 || c + dx >= m)
		{
			dx *= -1;
			dy *= -1;
		}

		r += dy;
		c += dx;

		roll(dice, direction);

		// todo : get score
		//cout << r << " " << c << " " << score[r][c] << endl;
		finalResult += score[r][c];

		if (get<0>(dice) > board[r][c])
		{
			rotate(direction, 1);
		}
		else if (get<0>(dice) < board[r][c])
		{
			rotate(direction, -1);
		}
	}

	cout << finalResult << '\n';

	return 0;
}