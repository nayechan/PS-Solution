#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int find(vector<int>& root, int u)
{
	while (root[u] != u)
	{
		u = root[u];
	}

	return u;
}

void union_root(vector<int>& root, vector<int>& rank, vector<pair<int, int>>& data, int u, int v)
{
	int u2 = find(root, u);
	int v2 = find(root, v);
	if (root[u2] == root[v2])
	{
		return;
	}

	else
	{
		if (rank[u2] == rank[v2])
		{
			root[u2] = v2;
			rank[v2]++;

			data[v2] = { data[u2].first + data[v2].first, data[u2].second + data[v2].second };
		}

		else if (rank[u2] < rank[v2])
		{
			root[u2] = root[v2];
			data[v2] = { data[u2].first + data[v2].first, data[u2].second + data[v2].second };
		}

		else
		{
			root[v2] = root[u2];
			data[u2] = { data[u2].first + data[v2].first, data[u2].second + data[v2].second };
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m, q;
	cin >> n >> m >> q;

	vector<int> tank(n);
	vector<int> root(n);
	vector<int> rank(n, 0);
	vector<pair<int, int>> data(n);
	iota(root.begin(), root.end(), 0);

	for (int i = 0; i < n; ++i)
	{
		int input;
		cin >> input;

		if (input == 0)
			data[i] = { 1, 0 };

		else
			data[i] = { 0, 1 };
	}

	for (int i = 0; i < m; ++i)
	{
		int u, v;
		cin >> u >> v;
		--u; --v;

		union_root(root, rank, data, u, v);
	}

	for (int i = 0; i < q; ++i)
	{
		int k;
		cin >> k;
		--k;

		int k2 = find(root, k);

		if (data[k2].first < data[k2].second)
		{
			cout << 1 << '\n';
		}
		else
		{
			cout << 0 << '\n';
		}
	}

	return 0;
}