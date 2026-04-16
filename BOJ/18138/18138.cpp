#include <iostream>
#include <vector>
#include <queue>
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

	vector<int> t(n), k(m);
	vector<vector<int>> graph(n);

	for (int i = 0; i < n; ++i)
	{
		cin >> t[i];
	}

	for (int i = 0; i < m; ++i)
	{
		cin >> k[i];
	}

	for (int i = 0; i < n; ++i)
	{
		int w = t[i];
		for (int j = 0; j < m; ++j)
		{
			int kara = k[j];
			if ((w * 2 <= kara * 4 && kara * 4 <= w * 3) || (w * 4 <= kara * 4 && kara * 4 <= w * 5))
			{
				graph[i].push_back(j);
			}
		}
	}

	cout << bimatch(graph, n, m) << "\n";

	return 0;
}