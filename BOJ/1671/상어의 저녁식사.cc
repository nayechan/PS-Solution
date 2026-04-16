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

int cmp(vector<tuple<int,int,int>>& data, int i, int j)
{
	auto [ax, ay, az] = data[i];
	auto [bx, by, bz] = data[j];

	if (ax == bx && ay == by && az == bz)
	{
		return (i<j)?-1:1;
	}

	if (ax <= bx && ay <= by && az <= bz)
	{
		return -1;
	}

	if (ax >= bx && ay >= by && az >= bz)
	{
		return 1;
	}

	return 0;
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	vector<vector<int>> graph(2*n);
	vector<int> match(n, -1);
	vector<int> visited(n, 0);

	vector<tuple<int, int, int>> data(n);

	for (int i = 0; i < n; ++i)
	{
		auto& [a, b, c] = data[i];
		cin >> a >> b >> c;
	}

	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			int result = cmp(data, i, j);

			if (result == 0) continue;

			if (result == -1)
			{
				graph[j].push_back(i);
				graph[n+j].push_back(i);
			}
			else
			{
				graph[i].push_back(j);
				graph[n+i].push_back(j);
			}
		}
	}

	cout << n - bimatch(graph, 2*n, n) << "\n";

	return 0;
}