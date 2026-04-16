#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>
#include <climits>

using namespace std;

constexpr long long INF = LLONG_MAX>>1;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n;
	cin >> n;

	vector<vector<long long>> parent(20, vector<long long>(n, -1));
	vector<vector<long long>> dist(20, vector<long long>(n, INF));

	vector<vector<pair<long long,long long>>> tree(n);
	vector<long long> energy(n);

	for (long long i = 0; i < n; ++i)
	{
		cin >> energy[i];
	}

	for (long long i = 0; i < n-1; ++i)
	{
		long long a, b, c;
		cin >> a >> b >> c;
		--a; --b;

		tree[a].push_back({b, c});
		tree[b].push_back({a, c});
	}

	queue<long long> q;
	vector<bool> visited(n, false);

	visited[0] = true;
	parent[0][0] = -1;
	dist[0][0] = 0;

	q.push(0);

	while (!q.empty())
	{
		const auto current = q.front();
		q.pop();

		for (const auto [next, nextCost] : tree[current])
		{
			if (!visited[next])
			{
				visited[next] = true;
				parent[0][next] = current;
				dist[0][next] = nextCost;
				q.push(next);
			}
		}
	}

	for (long long i = 1; i < 20; ++i)
	{
		for (long long j = 0; j < n; ++j)
		{
			if (parent[i - 1][j] != -1)
			{
				parent[i][j] = parent[i - 1][parent[i - 1][j]];
				dist[i][j] = dist[i - 1][j] + dist[i - 1][parent[i-1][j]];
			}
			else
			{
				parent[i][j] = -1;
				dist[i][j] = INF;
			}
		}
	}

	for (int i = 0; i < n; ++i)
	{
		long long currentEnergy = energy[i];
		int current = i;
		long long total = 0;
		for (long long j = 19; j >= 0; --j)
		{
			if (parent[j][current] != -1 && dist[j][current] <= currentEnergy) {
				currentEnergy -= dist[j][current];
				current = parent[j][current];
			}
		}

		cout << current+1 << '\n';
	}


	return 0;
}