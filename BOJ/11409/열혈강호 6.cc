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
	ll cost = 0;
};

bool spfa(vector<vector<Edge>>& graph, vector<ll>& dist, vector<bool>& present,
	vector<ll>& prevV, vector<ll>& prevE, ll s, ll t, ll n) {
	fill(dist.begin(), dist.end(), INF);
	fill(present.begin(), present.end(), false);

	dist[s] = 0;
	queue<ll> q;
	q.push(s);
	present[s] = true;

	while (!q.empty())
	{
		ll current = q.front();
		q.pop();

		present[current] = false;

		ll edgeCount = graph[current].size();
		for (ll i = 0; i < edgeCount; ++i)
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

pair<ll, ll> mcmf(vector<vector<Edge>>& graph, ll s, ll t)
{
	ll totalFlow = 0, totalCost = 0;

	ll n = graph.size();

	vector<ll> dist(n), prevV(n), prevE(n);
	vector<bool> present(n);


	while (spfa(graph, dist, present, prevV, prevE, s, t, n))
	{
		ll flow = INF;
		for (ll current = t; current != s; current = prevV[current])
		{
			auto& edge = graph[prevV[current]][prevE[current]];
			flow = min(flow, edge.cap - edge.flow);
		}

		for (ll current = t; current != s; current = prevV[current])
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

ll addEdge(vector<vector<Edge>>& graph, ll i, ll j, ll cap, ll cost = 0)
{
	ll revI = graph[j].size(), revJ = graph[i].size();
	graph[i].push_back({ j, revI, cap, 0, cost });
	graph[j].push_back({ i, revJ, 0, 0, -cost });

	return revJ;
}

// addEdge 할 때, i == j인 간선이나 cap == 0 인 간선 추가 안하도록 조심


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ll n, m, k;
	cin >> n >> m;

	vector<vector<Edge>> graph(n+m+2);
	vector <ll> level(n+m+2, 0);
	vector<ll> work(n+m+2, 0);

	for (ll i = 1; i <= n; ++i)
	{
		addEdge(graph, 0, i, 1);
	}

	for (ll i = 1; i <= m; ++i)
	{
		addEdge(graph, n+i, n+m+1, 1);
	}

	for (ll i = 1; i <= n; ++i)
	{
		ll count;
		cin >> count;
		for (ll j = 0; j < count; ++j)
		{
			ll target, cost;
			cin >> target >> cost;
			addEdge(graph, i, n+target, 1, -cost);
		}
	}

	auto [flow, cost] = mcmf(graph, 0, n + m + 1);
	cout << flow << "\n";
	cout << -cost << "\n";

	return 0;
}