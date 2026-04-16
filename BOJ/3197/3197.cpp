#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

pair<int, int> find_root(vector<vector<pair<int, int>>>& root, pair<int, int> v)
{
	pair<int, int> r = v;

	while (r != root[r.first][r.second])
		r = root[r.first][r.second];

	while (v != r)
	{
		auto parent = root[v.first][v.second];
		root[v.first][v.second] = r;
		v = parent;
	}

	return r;
}

void union_root(vector<vector<pair<int, int>>>& root, 
	pair<int,int> u, pair<int,int> v)
{
	u = find_root(root, u);
	v = find_root(root, v);
	if (u == v) return;
	root[u.first][u.second] = root[v.first][v.second];
}

bool check_swan(vector<vector<pair<int, int>>>& root, vector<pair<int, int>>& swan)
{
	int swanCount = swan.size();

	for (int i = 1; i < swanCount; ++i)
	{
		if (find_root(root, swan[i]) != find_root(root, swan[i - 1]))
		{
			return false;
		}
	}

	return true;
}

void init(queue<pair<int,int>> &uberq, vector<vector<int>> &board, 
	vector<vector<pair<int, int>>> &root,
	vector<vector<bool>>& inUberq, vector<vector<bool>> &visited, pair<int,int> pos)
{
	if (visited[pos.first][pos.second] || board[pos.first][pos.second])
		return;

	int r = board.size(), c = board[0].size();

	queue<pair<int, int>> q;

	q.push(pos);
	visited[pos.first][pos.second] = true;


	int level = 0;
	while (!q.empty())
	{
		int sz = q.size();
		for (int _c = 0; _c < sz; ++_c)
		{
			auto current = q.front();
			q.pop();
			bool isAdjacent = false;

			for (int i = 0; i < 4; ++i)
			{
				int nx = current.first + dx[i];
				int ny = current.second + dy[i];

				if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;

				if (visited[nx][ny]) continue;
				if (board[nx][ny])
				{
					isAdjacent = true;
					continue;
				}

				pair<int, int> n = { nx,ny };

				for (int i = 0; i < 4; ++i)
				{
					int nnx = nx + dx[i];
					int nny = ny + dy[i];
					if (nnx < 0 || nnx >= r || nny < 0 || nny >= c) continue;
					if (board[nnx][nny]) continue;
					pair<int, int> nn = { nnx, nny };
					union_root(root, nn, n);
				}
				visited[nx][ny] = true;
				q.push(n);
			}

			if (isAdjacent && !inUberq[current.first][current.second])
			{
				uberq.push(current);
				inUberq[current.first][current.second] = true;
			}
		}

		++level;
	}
}

int bfs(queue<pair<int, int>>& q, vector<vector<int>>& board,
	vector<pair<int,int>>& swan, vector<vector<pair<int, int>>>& root)
{
	int r = board.size(), c = board[0].size();

	int level = 0;
	bool isConnected = false;
	if (check_swan(root, swan))
	{
		return 0;
	}
	while (!q.empty())
	{
		++level;

		int sz = q.size();
		for (int _c = 0; _c < sz; ++_c)
		{
			auto current = q.front();

			q.pop();

			for (int i = 0; i < 4; ++i)
			{
				int nx = current.first + dx[i];
				int ny = current.second + dy[i];

				if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;

				pair<int, int> n = { nx,ny };
				if (board[nx][ny] == 0) continue;
				
				board[nx][ny] = 0;

				for (int i = 0; i < 4; ++i)
				{
					int nnx = nx + dx[i];
					int nny = ny + dy[i];
					if (nnx < 0 || nnx >= r || nny < 0 || nny >= c) continue;
					if (board[nnx][nny]) continue;
					pair<int, int> nn = { nnx, nny };
					union_root(root, nn, n);
				}

				q.push(n);
			}
		}

		if (check_swan(root, swan))
		{
			isConnected = true;
			break;
		}
	}

	return isConnected ? level : -1;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int r, c;
	cin >> r >> c;

	vector<vector<int>> board(r, vector<int>(c));
	vector<pair<int, int>> swan;
	vector<vector<pair<int, int>>> root(r, vector<pair<int,int>>(c));

	for (int i = 0; i < r; ++i)
	{
		string input; cin >> input;
		for (int j = 0; j < c; ++j)
		{
			char ch = input[j];

			board[i][j] = (ch == 'X') ? 1 : 0;

			if(ch == 'L')
				swan.push_back({ i,j });

			root[i][j] = { i, j };
		}
	}

	vector<vector<bool>> visited(r, vector<bool>(c,false));
	vector<vector<bool>> inUberq = vector<vector<bool>>(r, vector<bool>(c, false));

	queue<pair<int, int>> q;

	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			init(q, board, root, inUberq, visited, { i,j });
		}
	}

	visited.assign(r, vector<bool>(c, false));

	cout << bfs(q, board, swan, root) << '\n';



}