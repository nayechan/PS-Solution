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

ll addEdge(vector<vector<Edge>>& graph, ll i, ll j, ll cap, ll cost)
{
	ll revI = graph[j].size(), revJ = graph[i].size();
	graph[i].push_back({ j, revI, cap, 0, cost });
	graph[j].push_back({ i, revJ, 0, 0, -cost });

	return revJ;
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
		addEdge(graph, 0, i, count, 0);
	}

	for (ll i = 1; i <= m; ++i)
	{
		ll count; cin >> count;
		addEdge(graph, n + i, n + m + 1, count, 0);
	}

	for (ll i = 1; i <= m; ++i)
	{
		for (ll j = 1; j <= n; ++j)
		{
			ll cost; cin >> cost;

			addEdge(graph, j, i + n, INF, cost);
		}
	}

	pair<ll, ll> result = mcmf(graph, 0, n + m + 1);

	cout << result.second << '\n';

	return 0;
}