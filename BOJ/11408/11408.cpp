#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

constexpr int INF = 987654321;

using namespace std;

struct Edge {
	int to, rev;
	int cap, flow;
	int cost = 0;
};

bool spfa(vector<vector<Edge>>& graph, vector<int>& dist, vector<bool>& present, 
	vector<int> &prevV, vector<int>& prevE, int s, int t, int n) {
	fill(dist.begin(), dist.end(), INF);
	fill(present.begin(), present.end(), false);

	dist[s] = 0;
	queue<int> q;
	q.push(s);
	present[s] = true;

	while (!q.empty())
	{
		int current = q.front(); 
		q.pop();

		present[current] = false;

		int edgeCount = graph[current].size();
		for (int i=0;i<edgeCount;++i)
		{
			auto& edge = graph[current][i];
			if (edge.cap > edge.flow && dist[current] + edge.cost < dist[edge.to])
			{
				dist[edge.to] = dist[current] + edge.cost;
				prevV[edge.to] = current;
				prevE[edge.to] = i;

				if (!present[edge.to])
				{
					q.push(edge.to);
					present[edge.to] = true;
				}
			}
		}
	}

	return dist[t] != INF;	
}

pair<int, int> mcmf(vector<vector<Edge>>& graph, int s, int t)
{
	int totalFlow = 0, totalCost = 0;

	int n = graph.size();

	vector<int> dist(n), prevV(n), prevE(n);
	vector<bool> present(n);


	while (spfa(graph, dist, present, prevV, prevE, s, t, n))
	{
		int flow = INF;
		for (int current = t; current != s; current = prevV[current])
		{
			auto& edge = graph[prevV[current]][prevE[current]];
			flow = min(flow, edge.cap - edge.flow);
		}

		for (int current = t; current != s; current = prevV[current])
		{
			auto& edge = graph[prevV[current]][prevE[current]];
			edge.flow += flow;
			graph[current][edge.rev].flow -= flow;
		}

		totalFlow += flow;
		totalCost += flow * dist[t];
	}

	return { totalFlow, totalCost };
}

int addEdge(vector<vector<Edge>>& graph, int i, int j, int cap, int cost)
{
	int revI = graph[j].size(), revJ = graph[i].size();
	graph[i].push_back({ j, revI, cap, 0, cost });
	graph[j].push_back({ i, revJ, 0, 0, -cost });

	return revJ;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<vector<Edge>> graph(n + m + 2);

	for (int i = 1; i <= n; ++i)
	{
		addEdge(graph, 0, i, 1, 0);
	}

	for (int i = 1; i <= m; ++i)
	{
		addEdge(graph, n+i, n+m+1, 1, 0);
	}

	for (int i = 1; i <= n; ++i)
	{
		int count;
		cin >> count;

		for (int j = 0; j < count; ++j)
		{
			int to, cost;
			cin >> to >> cost;

			addEdge(graph, i, n + to, 1, cost);
		}
	}

	pair<int,int> result = mcmf(graph, 0, n + m + 1);

	cout << result.first << '\n' << result.second << '\n';

	return 0;
}