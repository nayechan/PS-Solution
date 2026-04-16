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

void addEdge(vector<vector<Edge>>& graph, int i, int j, int cap)
{
	int revI = graph[j].size(), revJ = graph[i].size();
	graph[i].push_back({ j, revI, cap, 0 });
	graph[j].push_back({ i, revJ, 0, 0 });
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<vector<Edge>> graph(n+2);

	vector<int> level(n+2);

	int totalFlow = 0;

	for (int i = 1; i <= n; ++i)
	{
		int input;
		cin >> input;

		if (input == 1)
		{
			addEdge(graph, 0, i, INF);
		}

		if (input == 2)
		{
			addEdge(graph, i, n+1, INF);
		}
	}

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			int cap;
			cin >> cap;

			if(cap != 0 && i!=j)
				addEdge(graph, i, j, cap);
		}
	}

	vector<int> work(n + 2, 0);
	while (bfs(graph, level, 0, n+1))
	{
		fill(work.begin(), work.end(), 0);
		while (true) {
			int flow = dfs(graph, level, work, 0, n+1, INF);
			if (flow == 0) break;
			totalFlow += flow;
		}
	}

	vector<int> a, b;

	for (int i = 1; i <= n; ++i)
	{
		if (level[i] == -1)
			b.push_back(i);
		else
			a.push_back(i);
	}
	
	cout << totalFlow << '\n';

	for (const auto& i : a)
		cout << i << " ";
	cout << '\n';
	for (const auto& i : b)
		cout << i << " ";
	cout << '\n'; 

	return 0;
}