#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<vector<pair<int,int>>> graph(n, vector<pair<int,int>>());

	for (int i = 0; i < m; ++i)
	{
		int u, v, c;
		cin >> u >> v >> c;
		--u; --v;
		graph[u].push_back({ c, v });
		graph[v].push_back({ c,u });
	}

	priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
	vector<int> dist(n, 987654321);

	pq.push({ 0, 0 });
	dist[0] = 0;


	while (!pq.empty())
	{
		auto [cost, current] = pq.top();
		pq.pop();

		if (dist[current] < cost) continue;

		dist[current] = cost;

		for (const auto& [nextCost, next] : graph[current])
		{
			if (dist[next] > dist[current] + nextCost)
			{
				pq.push({ dist[current] + nextCost , next });
			}
		}
	}

	cout << dist[n - 1] << endl;


	return 0;
}