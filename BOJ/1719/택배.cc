#include <iostream>
#include <vector>

using namespace std;

constexpr int INF = 987654321;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> dist(n, vector<int>(n, INF)), next(n, vector<int>(n, -1));

	for(int i=0;i<n;++i)
	{
		dist[i][i] = 0;
	}

	for (int i = 0; i < m; ++i)
	{

		int a, b, c;
		cin >> a >> b >> c;
		--a; --b;
		
		if (dist[a][b] > c)
		{
			dist[a][b] = c;
			next[a][b] = b;
		}
		if (dist[b][a] > c)
		{
			dist[b][a] = c;
			next[b][a] = a;
		}
	}

	for (int mid = 0; mid < n; ++mid)
	{
		for (int s = 0; s < n; ++s)
		{
			for (int e = 0; e < n; ++e)
			{
				if (dist[s][e] > dist[s][mid] + dist[mid][e])
				{
					dist[s][e] = dist[s][mid] + dist[mid][e];
					next[s][e] = next[s][mid];
				}
			}
		}
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (next[i][j] != -1)
				cout << next[i][j] + 1;
			else
				cout << '-';
			cout << ' ';
		}
		cout << '\n';
	}
	return 0;
}