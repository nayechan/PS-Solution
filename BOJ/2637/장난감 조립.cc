#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	int m;
	cin >> m;

	vector<int> degree(n+1, 0);
	vector<vector<int>> cost(n+1, vector<int>(n+1, 0));
	vector<vector<pair<int, int>>> edges(n+1);

	for (int i = 0; i < m; ++i)
	{
		int a, b, c;
		cin >> a >> b >> c;

		edges[b].push_back({ a, c });
		++degree[a];
	}

	queue<int> order;

	for (int i = 1; i <= n; ++i)
	{
		if (degree[i] == 0)
		{
			cost[i][i] = 1;
			order.push(i);
		}
	}

	while (!order.empty())
	{
		int current = order.front();
		order.pop();
		for (const auto& edge : edges[current])
		{
			int dest = edge.first;
			--degree[dest];
			if (degree[dest] <= 0)
			{
				order.push(edge.first);
			}
			for (int i = 1; i <= n; ++i)
			{
				cost[edge.first][i] += cost[current][i] * edge.second;
			}
		}
	}

	for (int i = 1; i <= n; ++i)
	{
		int count = cost[n][i];
		if (count > 0)
			cout << i << " " << count << endl;
	}

	return 0;
}