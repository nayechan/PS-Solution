#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using ll = long long;
constexpr ll INF = 987654321;

using namespace std;

bool dfs(int i, const vector<vector<int>>& graph,
	vector<int>& match, vector<int>& visited, int round) {
	for (int j : graph[i]) {
		if (visited[j] == round) continue;
		visited[j] = round;
		if (match[j] == -1 || dfs(match[j], graph, match, visited, round)) {
			match[j] = i;
			return true;
		}
	}
	return false;
}

int bimatch(const vector<vector<int>>& graph, int n, int m) {
	vector<int> match(n + m, -1);
	vector<int> visited(n + m, 0);
	int result = 0, round = 0;
	for (int i = 0; i < n; ++i) {
		if (dfs(i, graph, match, visited, ++round)) ++result;
	}
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	unordered_map<string, int> toNode;
	for (int i = 0; i < m; ++i)
	{
		string str;
		cin >> str;

		toNode[str] = i;
	}
	vector<vector<int>> graph(n);

	for (int i = 0; i < n; ++i)
	{
		int count; cin >> count;

		for (int j = 0; j < count; ++j)
		{
			string str;
			cin >> str;

			graph[i].push_back(toNode[str]);
		}
	}

	int result = bimatch(graph, n, m);

	if (result == n)
		cout << "YES\n";
	else
		cout << "NO\n" << result << "\n";

	return 0;
}