#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <tuple>

constexpr int INF = 987654321;

using namespace std;

int d[] = { 0,0,1,-1,0,0 };

int bfs(vector<vector<int>>& board, pair<int, int> s, pair<int, int> t, int dir = -1, int endDir = -1)
{
	int n = board.size(), m = board[0].size();
	vector<vector<vector<bool>>> visited(4, vector<vector<bool>>(n, vector<bool>(m, false)));
	queue<tuple<int, int, int>> q;

	if (dir == -1)
	{
		for (int i = 0; i < 4; ++i)
		{
			q.push({ i, s.first, s.second });
			visited[i][s.first][s.second] = true;
		}
	}
	else
	{
		q.push({ dir, s.first, s.second });
		visited[dir][s.first][s.second] = true;
	}
	int dist = 0;
	while (!q.empty())
	{
		int count = q.size();
		for (int i = 0; i < count; ++i)
		{
			auto [dir, px, py] = q.front(); q.pop();

			if (px == t.first && py == t.second)
			{
				if (dir == endDir || endDir == -1)
					return dist;
			}

			for (int _dir = 0; _dir < 4; ++_dir)
			{
				if (dir == _dir) continue;

				pair<int, int> newPos = { px + d[_dir], py + d[_dir + 2] };

				if (newPos.first < 0 || newPos.first >= n || newPos.second < 0 || newPos.second >= m)
					continue;

				if (visited[_dir][newPos.first][newPos.second])
					continue;

				if (board[newPos.first][newPos.second] == 1)
					continue;

				q.push({ _dir, newPos.first, newPos.second });
				visited[_dir][newPos.first][newPos.second] = true;
			}
		}
		++dist;
	}

	return INF;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> board(n, vector<int>(m,0));

	pair<int, int> s;
	vector<pair<int, int>> T;

	for (int i = 0; i < n; ++i)
	{
		string input;
		cin >> input;
		for (int j = 0; j < m; ++j)
		{
			char ch = input[j];
			if (ch == 'S')
			{
				board[i][j] = 0;
				s = { i,j };
			}
			else if (ch == 'C') 
			{
				board[i][j] = 0;
				T.push_back({ i,j });
			}
			else if (ch == '.')
			{
				board[i][j] = 0;
			}
			else if(ch == '#')
			{
				board[i][j] = 1;
			}
		}
	}

	int StoT1[4], StoT2[4], T1toT2[4], T2toT1[4];

	for (int i = 0; i < 4; ++i)
	{
		StoT1[i] = bfs(board, s, T[0], -1, i);
	}

	for (int i = 0; i < 4; ++i)
	{
		StoT2[i] = bfs(board, s, T[1], -1, i);
	}

	for (int i = 0; i < 4; ++i)
	{
		T1toT2[i] = bfs(board, T[0], T[1], i, -1);
	}

	for (int i = 0; i < 4; ++i)
	{
		T2toT1[i] = bfs(board, T[1], T[0], i, -1);
	}

	int result = INF;

	for (int i = 0; i < 4; ++i)
	{
		result = min(result, StoT1[i] + T1toT2[i]);
	}

	for (int i = 0; i < 4; ++i)
	{
		result = min(result, StoT2[i] + T2toT1[i]);
	}

	if (result == INF) result = -1;

	cout << result << '\n';


	return 0;
}