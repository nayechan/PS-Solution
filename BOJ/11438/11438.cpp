#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int INF = 987654321;

void dfs(vector<vector<int>>& graph, vector<vector<int>>& parent, vector<int>& level, int index, int prev = -1)
{
	level[index] = prev==-1 ? 0 : level[prev] + 1;
	parent[index][0] = prev;

	for (const auto& child : graph[index])
	{
		if (child == prev) continue;
		dfs(graph, parent, level, child, index);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<vector<int>> graph(n);

	vector<vector<int>> parent(n, vector<int>(20, -1));
	vector<int> level(n);

	for (int i = 0; i < n - 1; ++i)
	{
		int a, b;
		cin >> a >> b;
		--a;
		--b;

		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	dfs(graph, parent, level, 0);

	for (int k = 1; k < 20; k++) {
		for (int i = 0; i < n; i++) {
			if (parent[i][k - 1] != -1)
				parent[i][k] = parent[parent[i][k - 1]][k - 1];
			else
				parent[i][k] = -1;
		}
	}

	int m;
	cin >> m;
	for (int i = 0; i < m; ++i)
	{
		int u, v;
		cin >> u >> v;
		--u; --v;

		if (level[u] < level[v]) swap(u, v);

		int diff = level[u] - level[v];

		for (int i = 0; i < 20; ++i)
		{
			if (diff & (1 << i))
			{
				u = parent[u][i];
			}
		}

		if (u != v)
		{
			for (int i = 20 - 1; i >= 0; --i)
			{
				if (parent[u][i] != parent[v][i])
				{
					u = parent[u][i];
					v = parent[v][i];
				}
			}

			u = parent[u][0];
		}


		cout << u + 1 << '\n';
	}



	return 0;
}