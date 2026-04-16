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

	vector<vector<int>> data(n, vector<int>(m));

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cin >> data[i][j];
		}
	}

	vector<vector<int>> ldp(n, vector<int>(m, -1987654321)), rdp(n, vector<int>(m, -1987654321));

	rdp[0][0] = data[0][0];
	for (int i = 1; i < m; ++i)
	{
		rdp[0][i] = rdp[0][i - 1] + data[0][i];
	}

	for (int i = 1; i < n; ++i)
	{
		for (int j = m-1; j >= 0; --j)
		{
			ldp[i][j] = max(ldp[i - 1][j], rdp[i - 1][j]);
			if (j < m - 1)
				ldp[i][j] = max(ldp[i][j + 1], ldp[i][j]);
			ldp[i][j] += data[i][j];
		}

		for (int j=0; j<m; ++j)
		{
			rdp[i][j] = max(ldp[i - 1][j], rdp[i - 1][j]);
			if (j > 0)
				rdp[i][j] = max(rdp[i][j - 1], rdp[i][j]);
			rdp[i][j] += data[i][j];
		}
	}

	cout << rdp[n - 1][m - 1] << '\n';

	

	return 0;
}