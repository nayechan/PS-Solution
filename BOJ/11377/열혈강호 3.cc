#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>
#include <climits>

using namespace std;

constexpr int INF = 987654321;

struct Edge {
	int to;
	int cap;
	int flow;
	int rev;
};

void addEdge(vector<vector<Edge>> &flow, int from, int to, int cap)
{
	int fromSize = flow[from].size(), toSize = flow[to].size();

	flow[from].push_back({ to, cap, 0, toSize });
	flow[to].push_back({ from, 0, 0, fromSize });
}

int edmondKarp(vector<vector<Edge>>& flow, int s, int t)
{
	int result = 0;
	int flowSize = flow.size();

	while (true) {
		vector<int> parent(flowSize, -1);
		vector<int> edgeIndex(flowSize, -1);

		queue<int> q;
		q.push(s);
		parent[s] = s; 
		
		while (!q.empty() && parent[t] == -1) {
			int current = q.front();
			q.pop();

			int edgeCount = flow[current].size();
			for (int i = 0; i < edgeCount; ++i)
			{
				const auto& edge = flow[current][i];
				if (edge.cap - edge.flow > 0 && parent[edge.to] == -1) {
					q.push(edge.to);
					parent[edge.to] = current;
					edgeIndex[edge.to] = i;
				}
			}
		}

		if (parent[t] == -1) break;

		int minFlow = INF;
		for (int v = t; v != s; v = parent[v])
		{
			int u = parent[v];
			int idx = edgeIndex[v];
			minFlow = min(minFlow, flow[u][idx].cap - flow[u][idx].flow);
		}
		for (int v = t; v != s; v = parent[v])
		{
			int u = parent[v];
			int idx = edgeIndex[v];
			int revIdx = flow[u][idx].rev;

			flow[u][idx].flow += minFlow;
			flow[v][revIdx].flow -= minFlow;
		}
		result += minFlow;

	}
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m, k;
	cin >> n >> m >> k;

	// s -> N/B -> E -> J -> t (1 / 2 / n / m / 1)
	vector<vector<Edge>> flow(n+m+4);

	addEdge(flow, 0, 1, n);
	addEdge(flow, 0, 2, k);

	for (int i = 0; i < n; ++i)
	{
		addEdge(flow, 1, i + 3, 1);
		addEdge(flow, 2, i + 3, 1);
	}

	for (int i = 0; i < n; ++i)
	{
		int count;
		cin >> count;

		for (int j = 0; j < count; ++j)
		{
			int to;
			cin >> to;
			--to;

			addEdge(flow, i + 3, n + 3 + to, 1);
		}
	}

	for (int i = 0; i < m; ++i)
	{
		addEdge(flow, i + n + 3, n + m + 3, 1);
	}

	cout << edmondKarp(flow, 0, n + m + 3) << '\n';

	return 0;
}