#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

int dfs(vector<vector<int>>& graph, vector<bool>& visited, int i)
{
	visited[i] = true;

	if (graph[i].size() == 0) return 1;

	int sum = 1;

	for (const auto& e : graph[i])
	{
		if (visited[e]) continue;
		sum += dfs(graph, visited, e);
	}

	return sum;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<int> inedge(n, 0);
	vector<vector<int>> graph(n), invGraph(n);

	for (int i = 0; i < m; ++i)
	{
		int a, b;
		cin >> a >> b;
		--a; --b;
		graph[a].push_back(b);
		invGraph[b].push_back(a);
	}

	int count = 0;

	vector<bool> visited(n, false);
	for (int i = 0; i < n; ++i)
	{
		fill(visited.begin(), visited.end(), false);
		int current = 0;
		current += dfs(graph, visited, i);
		fill(visited.begin(), visited.end(), false);
		current += dfs(invGraph, visited, i);

		if (current == n + 1)
			++count;
	}

	cout << count << '\n';
	
	return 0;
}