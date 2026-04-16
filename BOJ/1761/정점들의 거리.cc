#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

constexpr int INF = 987654321;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<vector<int>> parent(16, vector<int>(n));
	vector<vector<pair<int,int>>> tree(n);

	for (int i = 0; i < n-1; ++i)
	{
		int u, v, c;
		cin >> u >> v >> c;
		--u; --v;

		tree[u].push_back({ v,c });
		tree[v].push_back({ u,c });
	}

	queue<pair<int,int>> q;
	vector<int> dist(n, INF);
	vector<int> depth(n, INF);
	vector<bool> visited(n, false);
	depth[0] = 0;
	visited[0] = true;
	dist[0] = 0;
	q.push({0,0});

	while (!q.empty())
	{
		auto [current, cost] = q.front();
		q.pop();

		for (const auto [next, nextCost] : tree[current])
		{
			if (visited[next])
				continue;
			dist[next] = cost + nextCost;
			depth[next] = depth[current] + 1;
			visited[next] = true;
			parent[0][next] = current;
			q.push({ next, dist[next] });
		}
	}

	parent[0][0] = 0;

	for (int i = 1; i < 16; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			parent[i][j] = parent[i-1][parent[i-1][j]];
		}
	}

	int m;
	cin >> m;

	for (int i = 0; i < m; ++i)
	{
		int u, v;
		cin >> u >> v;
		--u; --v;

		int _u = u, _v = v;
		if (depth[_u] < depth[_v])
			swap(_u, _v);

		int diff = depth[_u] - depth[_v];
		int level = 0;
		while(diff > 0)
		{
			if (diff & 1)
			{
				_u = parent[level][_u];
			}
			diff >>= 1;
			++level;
		}


		for (int i = 15; i >= 0; --i)
		{
			if (parent[i][_u] != parent[i][_v])
			{
				_u = parent[i][_u];
				_v = parent[i][_v];
			}
		}

		if (_u != _v)
		{
			_u = parent[0][_u];
		}

		int totalDist = dist[u] + dist[v] - 2 * dist[_u];
		cout << totalDist << "\n";
	}

	return 0;
}