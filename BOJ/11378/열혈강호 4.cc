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

using ll = long long;
constexpr ll INF = 1e18;

struct Edge {
	ll to, rev;
	ll cap, flow;
};

bool bfs(vector<vector<Edge>>& graph, vector<ll>& level, ll s, ll t)
{
	fill(level.begin(), level.end(), -1);
	queue<ll> q;
	q.push(s);
	level[s] = 0;

	while (!q.empty())
	{
		ll current = q.front();
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

ll dfs(vector<vector<Edge>>& graph, vector<ll>& level, vector<ll>& work,
	ll s, ll t, ll flow)
{
	if (s == t) return flow;

	for (ll& edgeIdx = work[s]; edgeIdx < graph[s].size(); ++edgeIdx)
	{
		Edge& edge = graph[s][edgeIdx];

		if (level[edge.to] == level[s] + 1 && edge.flow < edge.cap)
		{
			ll addFlow = dfs(graph, level, work, edge.to, t, min(flow, edge.cap - edge.flow));

			if (addFlow > 0) {
				edge.flow += addFlow;
				graph[edge.to][edge.rev].flow -= addFlow;
				return addFlow;
			}
		}
	}

	return 0;
}

ll addEdge(vector<vector<Edge>>& graph, ll i, ll j, ll cap)
{
	ll revI = graph[j].size(), revJ = graph[i].size();
	graph[i].push_back({ j, revI, cap, 0 });
	graph[j].push_back({ i, revJ, 0, 0 });

	return revJ;
}

ll dinic(vector<vector<Edge>>& graph, vector<ll>& level, vector<ll>& work, ll s, ll t)
{
	ll totalFlow = 0;
	while (bfs(graph, level, s, t))
	{
		fill(work.begin(), work.end(), 0);
		while (true) {
			ll flow = dfs(graph, level, work, s, t, INF);
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

	ll n, m, k;
	cin >> n >> m >> k;

	vector<vector<Edge>> graph(n+m+3);
	vector <ll> level(n+m+3, 0);
	vector<ll> work(n+m+3, 0);

	for (int i = 1; i <= n; ++i)
	{
		addEdge(graph, 0, i, 1);
	}

	addEdge(graph, 0, n+m+1, k);

	for (int i = 1; i <= n; ++i)
	{
		addEdge(graph, n+m+1, i, k);
	}

	for (int i = 1; i <= m; ++i)
	{
		addEdge(graph, n+i, n+m+2, 1);
	}

	for (int i = 1; i <= n; ++i)
	{
		int count;
		cin >> count;
		for (int j = 0; j < count; ++j)
		{
			int target; cin >> target;
			addEdge(graph, i, n+target, 1);
		}
	}

	cout << dinic(graph, level, work, 0, n+m+2) << "\n";

	return 0;
}