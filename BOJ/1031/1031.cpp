#include <iostream>
#include <vector>
#include <queue>

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

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<vector<Edge>> graph(n+m+2);

	vector<int> level(n+m+2);
	vector<int> teamA(n), teamB(m);

	int totalFlow = 0;

	for (int i = 1; i <= n; ++i)
	{
		cin >> teamA[i-1];
		addEdge(graph, 0, i, teamA[i - 1]);
	}
	for (int i = n+1; i <= n+m; ++i)
	{
		cin >> teamB[i-n-1];
		addEdge(graph, i, n+m+1, teamB[i-n-1]);
	}

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			addEdge(graph, i, j + n, 1);
		}
	}

	vector<int> work(n+m+2, 0);
	totalFlow = dinic(graph, level, work, 0, n + m + 1);

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			Edge& e = graph[i][j];

			Edge& s = graph[0][i - 1];
			Edge& t = graph[n + m + 1][j - 1];
			if (e.flow == 1) {
				e.flow = 0;
				graph[e.to][e.rev].flow = 0;

				s.flow--;
				graph[s.to][s.rev].flow++;

				t.flow++;
				graph[t.to][t.rev].flow--;

				int tempCap = e.cap;
				e.cap = 0;

				if (!dinic(graph, level, work, 0, n + m + 1)) {
					e.flow = 1;
					graph[e.to][e.rev].flow = -1;

					s.flow++;
					graph[s.to][s.rev].flow--;

					t.flow--;
					graph[t.to][t.rev].flow++;

					e.cap = tempCap;
				}
			}
			else {
				e.cap = 0;
			}
		}
	}

	bool isValid = true;

	for (int i = 0; i < n; ++i)
	{
		int sum = 0;
		for (int j = 0; j < m; ++j)
		{
			sum += graph[i+1][j+1].flow;
		}

		if (sum != teamA[i])
		{
			isValid = false;
			break;
		}
	}

	for (int j = 0; j < m; ++j)
	{
		int sum = 0;
		for (int i = 0; i < n; ++i)
		{
			sum += graph[i+1][j+1].flow;
		}

		if (sum != teamB[j])
		{
			isValid = false;
			break;
		}
	}

	if (isValid)
	{
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= m; ++j)
			{
				cout << graph[i][j].flow;
			}
			cout << '\n';
		}
	}
	else
	{
		cout << "-1\n";
	}

	return 0;
}