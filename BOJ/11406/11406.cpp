#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using ll = long long;
constexpr ll INF = 987654321;

using namespace std;

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

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ll n, m;
	cin >> n >> m;

	vector<vector<Edge>> graph(n + m + 2);

	for (ll i = 1; i <= n; ++i)
	{
		ll count; cin >> count;
		addEdge(graph, 0, i, count);
	}

	for (ll i = 1; i <= m; ++i)
	{
		ll count; cin >> count;
		addEdge(graph, n + i, n + m + 1, count);
	}

	for (ll i = 1; i <= m; ++i)
	{
		for (ll j = 1; j <= n; ++j)
		{
			ll cost; cin >> cost;

			addEdge(graph, j, i + n, cost);
		}
	}

	vector<ll> level(n+m+2, 0);
	vector<ll> work(n+m+2, 0);
	ll result = dinic(graph, level, work, 0, n + m + 1);

	cout << result << '\n';

	return 0;
}