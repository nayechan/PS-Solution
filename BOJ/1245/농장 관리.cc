#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

template <typename T> using vv = vector<vector<T>>;
typedef pair<int, int> pi;

bool isValid(int i, int j, int n, int m)
{
	if (i < 0 || j < 0) return false;
	if (i >= n || j >= m) return false;
	return true;
}

void bfs(vv<int>& board, vv<bool>& visited, int i, int j)
{
	int n = board.size();
	int m = board[0].size();

	vector<pi> delta = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };

	queue<pi> q;
	q.push({ i,j });
	visited[i][j] = true;

	while (!q.empty())
	{
		pi current = q.front();
		q.pop();

		for (const auto& d : delta)
		{
			pi next = { current.first + d.first, current.second + d.second };

			if (!isValid(next.first, next.second, n, m) ||
				visited[next.first][next.second])
				continue;

			if (board[current.first][current.second] < board[next.first][next.second]) 
				continue;

			q.push(next);
			visited[next.first][next.second] = true;
		}
	}
}

int main()
{
	int n, m;
	cin >> n >> m;

	vv<int> board(n, vector<int>(m));
	vv<bool> visited(n, vector<bool>(m, false));
	vector<pi> top;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cin >> board[i][j];
			top.push_back({i,j});
		}
	}

	sort(top.begin(), top.end(), [&board](const pi &a, const pi &b) {
		return board[a.first][a.second] > board[b.first][b.second];
		});

	int count = 0;

	for (const pi& p: top)
	{
		if (!visited[p.first][p.second])
		{
			bfs(board, visited, p.first, p.second);
			++count;
		}
	}

	cout << count << endl;

	return 0;
}