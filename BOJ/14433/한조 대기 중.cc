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

	int n, m, k1, k2;
	cin >> n >> m >> k1 >> k2;

	vector<vector<int>> graphA(n), graphB(n);

	for (int i = 0; i < k1; ++i)
	{
		int j, k;
		cin >> j >> k;
		graphA[j - 1].push_back(k - 1);
	}

	for (int i = 0; i < k2; ++i)
	{
		int j, k;
		cin >> j >> k;
		graphB[j - 1].push_back(k - 1);
	}

	int resultA = bimatch(graphA, n, m);
	int resultB = bimatch(graphB, n, m);

	if (resultA < resultB)
		cout << "네 다음 힐딱이" << "\n";
	else
		cout << "그만 알아보자" << "\n";

	return 0;
}