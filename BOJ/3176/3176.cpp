#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

constexpr long long INF = 1e18;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n;
	cin >> n;

	vector<vector<long long>> parent(20, vector<long long>(n));
	vector<vector<long long>> minDist(20, vector<long long>(n, INF));
	vector<vector<long long>> maxDist(20, vector<long long>(n, -INF));
	vector<vector<pair<long long, long long>>> tree(n);

	for (long long i = 0; i < n - 1; ++i)
	{
		long long u, v, c;
		cin >> u >> v >> c;
		--u; --v;

		tree[u].push_back({ v,c });
		tree[v].push_back({ u,c });
	}

	queue<long long> q;
	vector<long long> depth(n, INF);
	vector<bool> visited(n, false);
	depth[0] = 0;
	visited[0] = true;
	q.push(0);

	while (!q.empty())
	{
		long long current = q.front();
		q.pop();

		for (const auto [next, nextCost] : tree[current])
		{
			if (visited[next])
				continue;
			depth[next] = depth[current] + 1;
			visited[next] = true;
			parent[0][next] = current;
			minDist[0][next] = nextCost;
			maxDist[0][next] = nextCost;
			q.push(next);
		}
	}

	parent[0][0] = 0;
	maxDist[0][0] = -INF;
	minDist[0][0] = INF;

	for (long long i = 1; i < 20; ++i)
	{
		for (long long j = 0; j < n; ++j)
		{
			parent[i][j] = parent[i - 1][parent[i - 1][j]];
			minDist[i][j] = min(minDist[i - 1][j], minDist[i - 1][parent[i - 1][j]]);
			maxDist[i][j] = max(maxDist[i - 1][j], maxDist[i - 1][parent[i - 1][j]]);
		}
	}

	long long m;
	cin >> m;

	for (long long i = 0; i < m; ++i)
	{
		long long u, v;
		cin >> u >> v;
		--u; --v;

		long long _u = u, _v = v;
		long long minU = INF, maxU = -INF;
		long long minV = INF, maxV = -INF;

		if (depth[_u] < depth[_v])
			swap(_u, _v);

		long long diff = depth[_u] - depth[_v];
		long long level = 0;
		while (diff > 0)
		{
			if (diff & 1)
			{
				minU = min(minU, minDist[level][_u]);
				maxU = max(maxU, maxDist[level][_u]);
				_u = parent[level][_u];
			}
			diff >>= 1;
			++level;
		}


		for (long long i = 15; i >= 0; --i)
		{
			if (parent[i][_u] != parent[i][_v])
			{
				minU = min(minU, minDist[i][_u]);
				maxU = max(maxU, maxDist[i][_u]);
				minV = min(minV, minDist[i][_v]);
				maxV = max(maxV, maxDist[i][_v]);
				_u = parent[i][_u];
				_v = parent[i][_v];
			}
		}

		if (_u != _v)
		{
			minU = min(minU, minDist[0][_u]);
			maxU = max(maxU, maxDist[0][_u]);
			minV = min(minV, minDist[0][_v]);
			maxV = max(maxV, maxDist[0][_v]);
			_u = parent[0][_u];
		}

		cout << min(minU, minV) << " " << max(maxU, maxV) << "\n";
	}

	return 0;
}