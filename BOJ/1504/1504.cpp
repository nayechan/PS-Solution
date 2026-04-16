#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n, e;
	cin >> n >> e;

	vector<vector<pair<long long, long long>>> graph(n, vector <pair<long long, long long>>());

	for (long long i = 0; i < e; ++i)
	{
		long long a, b, c;
		cin >> a >> b >> c;

		--a; --b;

		graph[a].push_back({ c,b });
		graph[b].push_back({ c,a });
	}

	long long u, v;
	cin >> u >> v;
	--u; --v;

	vector<vector<long long>> dist(3, vector<long long>(n, 222222222));
	vector<long long> startNode = { 0, u, v };

	for (long long i = 0; i < 3; ++i)
	{
		dist[i][startNode[i]] = 0;
		priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;
		pq.push({ 0, startNode[i] });
		while (!pq.empty())
		{
			auto [cost, current] = pq.top();
			pq.pop();
			if (dist[i][current] < cost) continue;
			dist[i][current] = cost;

			for (const auto& [nextCost, next] : graph[current])
			{
				if (dist[i][next] > cost + nextCost)
				{
					pq.push({ cost + nextCost, next });
				}
			}
		}
	}

	// 1 -> u -> v -> n vs 1 -> v -> u -> n
	long long result = min(dist[0][u] + dist[1][v] + dist[2][n - 1], dist[0][v] + dist[2][u] + dist[1][n-1]);
	if (result >= 222222222) result = -1;
	cout << result << endl;
	
	return 0;
}