#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

pair<long long,long long> dfs1(vector<vector<pair<long long,long long>>>& tree, vector<long long> &down, 
	vector<long long> &sub, long long v, long long prev = -1)
{
	long long count = 0;
	long long weight = 0;
	for (const auto [next, dir] : tree[v])
	{
		if (prev == next) continue;
		auto [nextCount, nextWeight] = dfs1(tree, down, sub, next, v);

		count += nextCount + 1;
		weight += nextWeight;
		if (dir == -1)
		{
			weight += 1;
		}
	}

	sub[v] = count;
	down[v] = weight;

	return { count, weight };
}

void dfs2(vector<vector<pair<long long, long long>>>& tree, vector<long long>& up, vector<long long>& down,
	vector<long long>& sub, long long v, long long prev = -1, long long prevWeight = 0)
{
	long long n = tree.size();
	if (prev != -1)
	{
		up[v] = down[prev] + up[prev] - down[v];
		up[v] -= prevWeight;
		up[v] += (1 - prevWeight);
	}

	for (const auto [next, dir] : tree[v])
	{
		if (prev == next) continue;

		long long weight = 0;
		if (dir == -1) weight = 1;
		dfs2(tree, up, down, sub, next, v, weight);
	}
}



int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n;
	cin >> n;

	vector<vector<pair<long long, long long>>> tree(n);
	unordered_map<long long, long long> indice;

	for (long long i = 0; i < n-1; ++i)
	{
		long long u, v;
		cin >> u >> v;
		--u; --v;
		indice[(long long)u*n+v] = i;
		tree[u].push_back({ v, 1 });
		tree[v].push_back({ u, -1 });
	}

	vector<long long> down(n, 0), up(n, 0), sub(n, 0);
	dfs1(tree, down, sub, 0);
	dfs2(tree, up, down, sub, 0);

	long long minIdx = -1, _min = 987654321;

	for(long long i=0;i<n;++i)
	{
		if (_min > down[i] + up[i])
		{
			_min = down[i] + up[i];
			minIdx = i;
		}
	}

	vector<long long> isReversed(n-1, false);
	vector<bool> visited(n, false);
	visited[minIdx] = true;
	queue<long long> q;
	q.push(minIdx);

	while (!q.empty())
	{
		long long current = q.front(); q.pop();

		for (const auto[next, dir] : tree[current])
		{
			if (visited[next]) continue;
			visited[next] = true;
			q.push(next);

			pair<long long, long long> nextEdge = { current, next };
			if (dir == -1)
			{
				swap(nextEdge.first, nextEdge.second);
			}
			long long indiceNum = nextEdge.first * n + nextEdge.second;

			isReversed[indice[indiceNum]] = (dir == -1);
		}

	}

	for (long long i = 0; i < n-1; ++i)
	{
		cout << isReversed[i];
	}
	cout << "\n";

	return 0;
}