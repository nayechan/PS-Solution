#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>

using namespace std;
int edge[500500];
int incRoot[1001], decRoot[1001];

int find(int* root, int v)
{
	if (root[v] == v) return v;

	else return (root[v] = find(root, root[v]));
}

int union_root(int* root, int u, int v)
{
	int u2 = find(root, u);
	int v2 = find(root, v);

	if (u2 == v2) return 0;

	root[u2] = v2;
	return 1;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	int edgeCount = 0;

	for (int i = 0; i <= n; ++i)
	{
		incRoot[i] = i;
	}

	for (int i = 0; i <= n; ++i)
	{
		decRoot[i] = i;
	}

	for (int i = 0; i < m + 1; ++i)
	{
		int a, b, c;
		cin >> a >> b >> c;

		edge[edgeCount++] = ((c << 24) | (a << 12) | b);
	}

	int inc = 0, dec = 0;

	for (int i = 0; i < edgeCount; ++i)
	{
		int e = edge[i];

		((e >> 24) ? dec : inc) += union_root((e >> 24) ? decRoot : incRoot, (e >> 12) & 0xfff, e & 0xfff);
	}

	int result = (inc * inc) - ((n - dec) * (n - dec));
	cout << result << '\n';

	return 0;
}