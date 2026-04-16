#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

constexpr int INF = 987654321;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int m;
	cin >> m;

	vector<vector<int>> data(20, vector<int>(m, -1));

	for (int i = 0; i < m; ++i)
	{
		cin >> data[0][i];
		--data[0][i];
	}

	for (int i = 1; i < 20; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (data[i - 1][j] != -1)
				data[i][j] = data[i - 1][data[i - 1][j]];
			else
				data[i][j] = -1;
		}
	}

	int q;
	cin >> q;

	for (int i = 0; i < q; ++i)
	{
		int n, x;
		cin >> n >> x;
		--x;
		
		for (int j = 0; j < 20; ++j)
		{
			if (n & (1 << j))
			{
				x = data[j][x];
				if (x == -1) break;
			}
		}

		assert(x != -1);

		cout << x + 1 << '\n';
			
	}


	return 0;
}