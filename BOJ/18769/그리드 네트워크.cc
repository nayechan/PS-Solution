#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

long long find(vector<long long>& root, long long v)
{
	if (root[v] == v) return v;
	return root[v] = find(root, root[v]);
}

void union_root(vector<long long>& root, long long u, long long v)
{
	root[find(root, u)] = find(root, v);
}

void test()
{
	long long r, c;
	cin >> r >> c;

	vector<long long> root(r * c);
	iota(root.begin(), root.end(), 0LL);

	vector < vector<pair<long long,long long>>> edges(5LL);

	for(long long i=0LL;i<r;++i)
	{
		for (long long j = 0LL; j < c - 1LL; ++j)
		{
			long long cost;
			cin >> cost;
			edges[cost].push_back({i * c + j, i * c + j + 1LL});
			edges[cost].push_back({ i * c + j + 1LL, i * c + j });
		}
	}
	for (long long i = 0LL; i < r - 1LL; ++i)
	{
		for (long long j = 0LL; j < c; ++j)
		{
			long long cost;
			cin >> cost;
			edges[cost].push_back({ i * c + j, (i+1LL) * c + j });
			edges[cost].push_back({ (i+1LL) * c + j, i * c + j});
		}
	}

	long long count = 0LL;
	long long totalCost = 0LL;
	for (long long i = 1LL; i <= 4LL; ++i)
	{
		while (!edges[i].empty() && count < r * c - 1LL)
		{
			auto [from, to] = edges[i].back();
			edges[i].pop_back();

			if (find(root, from) != find(root, to))
			{
				totalCost += i;
				union_root(root, from, to);
			}
		}
	}

	cout << totalCost << '\n';
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	long long t;
	cin >> t;
	for (long long i = 0LL; i < t; ++i)
	{
		test();
	}
	return 0;
}