#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

using namespace std;

typedef pair<int, int> pi;
typedef pair<int, pi> ppi;

int find(vector<int>& root, int u)
{
	if (u != root[u])
	{
		root[u] = find(root, root[u]);
	}

	return root[u];
}

void union_root(vector<int>& root, vector<int>& rank, int u, int v)
{
	int u2 = find(root, u);
	int v2 = find(root, v);
	if (u2 == v2)
	{
		return;
	}

	else
	{
		if (rank[u2] == rank[v2])
		{
			root[u2] = v2;
			rank[v2]++;
		}

		else if (rank[u2] < rank[v2])
		{
			root[u2] = v2;
		}

		else
		{
			root[v2] = u2;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	auto comp = [](ppi& a, ppi& b)
	{
		return a.first > b.first;
	};
	priority_queue<ppi, vector<ppi>, decltype(comp)> edges(comp);

	vector<int> root(n);
	vector<int> rank(n, 0);
	iota(root.begin(), root.end(), 0);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			int input;
			cin >> input;

			if(i <= j)
				edges.push({ input, {i,j} });
		}
	}

	int count = 0, total = 0;
	vector<pi> newInstalled;

	while (!edges.empty())
	{
		ppi edge = edges.top();
		if (edge.first < 0 || find(root, edge.second.first) != find(root, edge.second.second))
		{
			union_root(root, rank, edge.second.first, edge.second.second);
			count += abs(edge.first);
			if (edge.first > 0)
			{
				++total;
				newInstalled.push_back(edge.second);
			}
		}
		edges.pop();
	}

	cout << count << " " << total << '\n';

	for (pi installedEdge : newInstalled)
	{
		cout << installedEdge.first+1 << " " << installedEdge.second+1 << '\n';
	}

	return 0;
}