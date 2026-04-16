#include <iostream>
#include <vector>
#include <queue>

#define INF 1012345678

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<vector<pair<int, int>>> graph(n);
	vector<int> dist(n, 0);
	for(int i=0;i<m;++i)
	{
		int a, b, c;
		cin >> a >> b >> c;
		--a;
		--b;
		graph[a].push_back({ c,b });
		graph[b].push_back({ c,a });
	}
	int s, t;
	cin >> s >> t;
	--s; --t;

	priority_queue<pair<int, int>> edges;
	edges.push({ INF,s });
	while (!edges.empty())
	{
		const auto [currentCost, currentNode] = edges.top();
		edges.pop();

		if (dist[currentNode] >= currentCost)
		{
			continue;
		}

		dist[currentNode] = currentCost;

		for (const auto& [newCost, newNode] : graph[currentNode])
		{
			int resultCost = min(currentCost, newCost);
			if (dist[newNode] >= resultCost)
				continue;
			edges.push({ resultCost, newNode });
		}
	}

	cout << dist[t] << endl;

	return 0;
}