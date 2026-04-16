#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 987654321

using namespace std;

//first : length, second : pos
void dijkstra(int start, vector<vector<pair<int, int>>>& graph, vector<int>& dist)
{
	priority_queue<pair<int, int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

	dist[start] = 0;
	pq.push({ 0, start });
	while (!pq.empty())
	{
		pair<int,int> current = pq.top();
		pq.pop();

		if (dist[current.second] < current.first)
			continue;

		for (const auto& [nextDist, nextDest] : graph[current.second])
		{
			if (dist[nextDest] > current.first + nextDist)
			{
				dist[nextDest] = current.first + nextDist;
				pq.push({ current.first + nextDist, nextDest });
			}
		}
	}

}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n;
	cin >> n;

	int a, b, c;
	cin >> a >> b >> c;
	--a; --b; --c;

	int m;
	cin >> m;

	vector<vector<pair<int, int>>> graph(n);

	for (int i = 0; i < m; ++i)
	{
		int a, b, c;
		cin >> a >> b >> c;
		--a; --b;

		graph[a].push_back({ c, b });
		graph[b].push_back({ c, a });
	}


	vector<vector<int>> dist(3, vector<int>(n, INF));
	dijkstra(a, graph, dist[0]);
	dijkstra(b, graph, dist[1]);
	dijkstra(c, graph, dist[2]);

	vector<pair<int, int>> result;

	dist[0][a] = INF;
	dist[1][b] = INF;
	dist[2][c] = INF;

	int maxIndex = -1;
	int maxValue = -INF;

	for (int i=n-1;i>=0;--i)
	{
		int d = min({ dist[0][i], dist[1][i], dist[2][i] });
		if (maxValue <= d)
		{
			maxIndex = i;
			maxValue = d;
		}
	}
	cout << maxIndex+1 << endl;
}