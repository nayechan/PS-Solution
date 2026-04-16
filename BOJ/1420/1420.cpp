#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

constexpr int INF = 987654321;

struct Edge {
	int to, rev;
	int cap, flow;
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

		for (const auto& e : graph[current])
		{
			if (level[e.to] >= 0) continue;
			if (e.flow >= e.cap) continue;

			level[e.to] = level[current] + 1;
			q.push(e.to);
		}
	}

	return level[t] != -1;
}

int dfs(vector<vector<Edge>>& graph, vector<int>& level, vector<int>& work,
	int s, int t, int flow)
{
	if (s == t) return flow;

	for (int& edgeIdx = work[s]; edgeIdx < graph[s].size(); ++edgeIdx)
	{
		Edge& edge = graph[s][edgeIdx];

		if (level[edge.to] == level[s] + 1 && edge.flow < edge.cap)
		{
			int addFlow = dfs(graph, level, work, edge.to, t, min(flow, edge.cap - edge.flow));

			if (addFlow > 0) {
				edge.flow += addFlow;
				graph[edge.to][edge.rev].flow -= addFlow;
				return addFlow;
			}
		}
	}

	return 0;
}

int addEdge(vector<vector<Edge>>& graph, int i, int j, int cap)
{
	int revI = graph[j].size(), revJ = graph[i].size();
	graph[i].push_back({ j, revI, cap, 0 });
	graph[j].push_back({ i, revJ, 0, 0 });
	//graph[j].push_back({ i, revJ, cap, 0 });

	return revJ;
}

int dinic(vector<vector<Edge>>& graph, vector<int>& level, vector<int>& work, int s, int t)
{
	int totalFlow = 0;
	while (bfs(graph, level, s, t))
	{
		fill(work.begin(), work.end(), 0);
		while (true) {
			int flow = dfs(graph, level, work, s, t, INF);
			if (flow == 0) break;
			totalFlow += flow;
		}
	}
	return totalFlow;
}

// addEdge 할 때, i == j인 간선이나 cap == 0 인 간선 추가 안하도록 조심

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> board(n, vector<int>(m, 0));

	pair<int, int> s, t;

	for (int i = 0; i < n; ++i)
	{
		string str;
		cin >> str;
		for (int j = 0; j < m; ++j)
		{
			char ch = str[j];

			if (ch == '#')
			{
				board[i][j] = 1;
			}

			if (ch == 'K')
			{
				s = { i, j };
			}

			if (ch == 'H')
			{
				t = { i, j };
			}
		}
	}

	vector<vector<Edge>> graph(n*m*2);

	auto toIn = [&m](pair<int, int> x) {
		return x.first * m + x.second;
		};

	auto toOut = [&n, &m](pair<int, int> x) {
		return n*m + x.first * m + x.second;
		};


	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			addEdge(graph, toIn({ i, j }), toOut({ i, j }), 1);
		}
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m - 1; ++j)
		{
			if (board[i][j] || board[i][j + 1])
				continue;

			addEdge(graph, toOut({ i, j }), toIn({ i, j + 1 }), INF);
			addEdge(graph, toOut({ i, j + 1 }), toIn({ i, j }), INF);
		}
	}
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (board[i][j] || board[i+1][j])
				continue;

			addEdge(graph, toOut({ i, j }), toIn({ i + 1, j }), INF);
			addEdge(graph, toOut({ i + 1, j }), toIn({ i, j }), INF);
		}
	}

	vector<int> level(n * m * 2, -1);
	vector<int> work(n * m * 2, 0);
	int result = dinic(graph, level, work, toOut(s), toIn(t));

	if (abs(s.first - t.first) + abs(s.second - t.second) <= 1 || result == INF)
		cout << "-1\n";
	else
		cout << result << "\n";


	return 0;
}