#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

constexpr long long INF = 987654321;

using namespace std;

struct Edge {
	int to, rev;
	int flow, cap;
};

bool bfs(vector<vector<Edge>>& graph, vector<int>& level, int s, int t)
{
	fill(level.begin(), level.end(), -1);
	queue<int> q;
	q.push(s);
	level[s] = 0;

	while (!q.empty())
	{
		int current = q.front();
		q.pop();
		int edgeCount = graph[current].size();

		for (int i = 0; i < edgeCount; ++i)
		{
			auto& edge = graph[current][i];

			if (level[edge.to] == -1 && edge.cap - edge.flow > 0)
			{
				q.push(edge.to);
				level[edge.to] = level[current] + 1;
			}
		}
	}

	return level[t] != -1;
}

int dfs(vector<vector<Edge>>& graph, vector<int>& level, vector<int>& work, int s, int t, int flow=INF)
{
	if (s == t) return flow;

	int edgeCount = graph[s].size();
	for (int &i = work[s]; i < edgeCount; ++i)
	{
		auto& edge = graph[s][i];
		int residual = min(flow, edge.cap - edge.flow);

		if (level[edge.to] != level[s] + 1 || residual <= 0) continue;

		int delta = dfs(graph, level, work, edge.to, t, residual);

		if (delta > 0)
		{
			edge.flow += delta;
			graph[edge.to][edge.rev].flow -= delta;
			return delta;
		}
	}
	return 0;
}

int dinic(vector<vector<Edge>>& graph, int s, int t)
{
	vector<int> level(graph.size());
	vector<int> work(graph.size());
	int totalFlow = 0;
	while (bfs(graph, level, s, t))
	{
		fill(work.begin(), work.end(), 0);
		while (true)
		{
			int flow = dfs(graph, level, work, s, t, INF);
			if (flow == 0) break;
			totalFlow += flow;
		}
	}

	return totalFlow;
}

void addEdge(vector<vector<Edge>>& graph, int i, int j, int cap)
{
	if (cap == 0 || i == j) return;
	int sizeI = graph[i].size(), sizeJ = graph[j].size();
	graph[i].push_back({ j, sizeJ, 0, cap });
	graph[j].push_back({ i, sizeI, 0, 0 });
}

void test()
{
	int n, m;
	cin >> n >> m;

	int total = 0;

	vector<vector<bool>> isBroken(n, vector<bool>(m));
	for (int i = 0; i < n; ++i)
	{
		string input;
		cin >> input;
		for (int j = 0; j < m; ++j)
		{
			isBroken[i][j] = (input[j] == 'x');
			total += (isBroken[i][j]) ? 0 : 1;
		}
	}

	vector<vector<Edge>> graph(n * m + 2);

	vector<int> dr = { -1, 0, 1, -1, 0, 1 };
	vector<int> dc = { -1, -1, -1, 1, 1, 1 };

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (isBroken[i][j])
				continue;

			if (j % 2 == 0)
			{
				addEdge(graph, 0, i * m + j + 1, 1);
				for (int k = 0; k < 6; ++k)
				{
					int nextR = i + dr[k];
					int nextC = j + dc[k];

					if (nextR < 0 || nextR >= n || nextC < 0 || nextC >= m)
						continue;

					addEdge(graph, i * m + j + 1, nextR * m + nextC + 1, INF);
				}
			}
			else
			{
				addEdge(graph, i * m + j + 1, n * m + 1, 1);
			}
		}
	}

	int result = dinic(graph, 0, n * m + 1);
	cout << total - result << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;

	for (int i = 0; i < t; ++i)
	{
		test();
	}	

	return 0;
}