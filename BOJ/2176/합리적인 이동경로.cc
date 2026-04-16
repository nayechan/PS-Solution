#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dfs(int u, int endV, vector<int> &dp, vector<int> &dist, const vector<vector<pair<int, int>>>& graph) {

	if (u == endV) {
		return 1;
	}
	if(dp[u] != -1) {
		return dp[u];
	}
	int totalPaths = 0;
	if(u != endV) {
		for (auto& [v, cost] : graph[u]) {
			if (dist[u] > dist[v]) {
				totalPaths += dfs(v, endV, dp, dist, graph);
			}
		}
	}

	dp[u] = totalPaths;
	return dp[u];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	priority_queue<pair<int, int>, vector<pair<int,int>>, less<pair<int,int>>> pq;
	int n, m;
	cin >> n >> m;

	vector<vector<pair<int, int>>> graph(n);

	for(int i=0;i<m;++i) {
		int a, b, cost;
		cin >> a >> b >> cost;
		--a; --b; 
		graph[a].push_back({b, cost});
		graph[b].push_back({a, cost});
	}

	vector<int> dist(n, INT32_MAX);

	if(n == 1) {
		cout << "0\n";
		return 0;
	}
	dist[1] = 0;
	pq.push({ 0, 1 });
	while(!pq.empty()) {
		auto [d, u] = pq.top();
		pq.pop();
		if(d > dist[u]) continue; // outdated entry
		for(auto [v, cost] : graph[u]) {
			if(dist[u] + cost < dist[v]) {
				dist[v] = dist[u] + cost;
				pq.push({ dist[v], v });
			}
		}
	}

	vector<int> dp(n, -1);
	

	cout << dfs(0, 1, dp, dist, graph) << "\n";


	return 0;
}