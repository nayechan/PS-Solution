#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <tuple>

using namespace std;

int find_root(vector<int>& root, int v)
{
	int current = v;
	while (root[current] != current)
	{
		current = root[current];
	}

	root[v] = current;

	return current;
}

void union_root(vector<int>& root, vector<int>& rank, int u, int v)
{
	int u2 = find_root(root, u);
	int v2 = find_root(root, v);

	if (u2 == v2) return;

	if (rank[u2] == rank[v2])
	{
		++rank[u2];
	}

	if (rank[u2] > rank[v2])
	{
		root[v2] = u2;
	}

	else
	{
		root[u2] = v2;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<vector<int>> data(n, vector<int>(n));
	vector<int> rank(n, 0);
	vector<int> root(n);
	auto comp = [](tuple<int,int,int>& a, tuple<int, int, int>& b) {
		return get<2>(a) > get<2>(b);
	};
	priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(comp)> pq(comp);
	iota(root.begin(), root.end(), 0);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> data[i][j];
			pq.push({i, j, data[i][j]});
		}
	}

	long long result = 0;
	while (!pq.empty())
	{
		auto& [a, b, dist] = pq.top();
		pq.pop();

		if (a == b) continue;

		if (find_root(root, a) != find_root(root, b))
		{
			result += dist;
			union_root(root, rank, a, b);
		}
	}

	cout << result << endl;

	return 0;
}