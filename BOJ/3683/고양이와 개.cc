#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include <unordered_map>
#include <deque>

using namespace std;

constexpr int INF = 987654321;

struct Edge {
	int to, rev;
	int cap, flow;
};

bool bfs(vector<vector<Edge>>& graph, vector<int> &level, int s, int t)
{
	fill(level.begin(), level.end(), -1);
	queue<int> q;
	q.push(s);
	level[s] = 0;

	while (!q.empty())
	{
		int current = q.front(); q.pop();

		for (const auto& e : graph[current])
		{
			if (level[e.to] != -1)
				continue;

			if (e.flow >= e.cap) continue;

			level[e.to] = level[current] + 1;
			q.push(e.to);
		}
	}

	return level[t] != -1;
}

int dfs(vector<vector<Edge>>& graph, vector<int>& level, vector<int>& work, int s, int t, int flow)
{
	if (s == t) return flow;

	for (int& edgeIdx = work[s]; edgeIdx < graph[s].size(); ++edgeIdx)
	{
		auto &e = graph[s][edgeIdx];

		if (level[s] + 1 != level[e.to])
			continue;

		if (e.flow >= e.cap) continue;

		int diff = min(flow, e.cap - e.flow);

		int result = dfs(graph, level, work, e.to, t, diff);

		if (result > 0)
		{
			e.flow += result;
			graph[e.to][e.rev].flow -= result;
			return result;
		}
	}
	return 0;
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

int addEdge(vector<vector<Edge>>& graph, int i, int j, int cap)
{
	int revI = graph[j].size(), revJ = graph[i].size();
	graph[i].push_back({ j, revI, cap, 0 });
	graph[j].push_back({ i, revJ, 0, 0 });

	return revJ;
}

void test()
{
	int c, d, v;
	cin >> c >> d >> v;

	vector<vector<Edge>> graph(v+2);
	vector<pair<int, int>> selection(v+1);

	for (int i = 1; i <= v; ++i)
	{
		string s1, s2;
		cin >> s1 >> s2;

		int param1 = (s1[0] - 'C') * c + atoi(s1.data() + 1) - 1;
		int param2 = (s2[0] - 'C') * c + atoi(s2.data() + 1) - 1;

		selection[i] = { param1, param2 };

		if (param1 >= c)
		{
			addEdge(graph, 0, i, 1);
		}
		else
		{
			addEdge(graph, i, v+1, 1);
		}
	}

	for (int i = 1; i < v; ++i)
	{
		for (int j = i + 1; j <= v; ++j)
		{
			const auto& p1 = selection[i];
			const auto& p2 = selection[j];

			if ((p1.first >= c) == (p2.first >= c))
				continue;

			if (p1.first == p2.second || p1.second == p2.first)
			{
				if (p1.first >= c)
				{
					addEdge(graph, i, j, 1);
				}
				else
				{
					addEdge(graph, j, i, 1);
				}
			}
		}
	}

	vector<int> level(v + 2, -1);
	vector<int> work(v + 2, 0);

	int result = v - dinic(graph, level, work, 0, v + 1);
	cout << result << "\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;
	for(int i=0;i<t;++i)
	{
		test();
	}

	return 0;
}