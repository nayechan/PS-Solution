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

void addEdge(vector<vector<Edge>>& flow, int from, int to, int cap)
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

	int n, m;
	cin >> n >> m;

	vector<vector<Edge>> flow(n+2);

	for (int i = 0; i < m; ++i)
	{
		int a, b, c;
		cin >> a >> b >> c;
		addEdge(flow, a, b, c);
		addEdge(flow, b, a, c);
	}
	
	int s, t;
	cin >> s >> t;

	//addEdge(flow, 0, s, INF);
	//addEdge(flow, t, n + 1, INF);

	cout << edmondKarp(flow, s, t) << '\n';

	return 0;
}