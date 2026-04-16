#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;


int main()
{
	int n, m, k;
	cin >> n >> m >> k;

	vector<vector<deque<int>>> trees(n, vector<deque<int>>(n));
	vector<vector<int>> initialDetergent(n, vector<int>(n, 0));


	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> initialDetergent[i][j];
		}
	}

	vector<vector<int>> detergent(n, vector<int>(n, 5));

	int count = m;

	for (int i = 0; i < m; ++i)
	{
		int x, y, z;
		cin >> x >> y >> z;
		--x; --y;

		trees[x][y].push_back(z);
	}

	vector<int> dx = { 1,0,-1,1,-1,1,0,-1 };
	vector<int> dy = { 1,1,1,0,0,-1,-1,-1 };

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			sort(trees[i][j].begin(), trees[i][j].end());
		}
	}

	for (int year = 0; year < k; ++year)
	{
		//spring & summer
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				int sz = trees[i][j].size();

				int dying = -1;
				for (int k=0; k<sz; ++k)
				{
					auto &tree = trees[i][j][k];
					if (detergent[i][j] >= tree)
					{
						detergent[i][j] -= tree;
						++tree;
					}
					else
					{
						dying = k;
						break;
					}
				}

				if (dying == -1) continue;

				for (int k = sz - 1; k >= dying; --k)
				{
					detergent[i][j] += (trees[i][j].back() / 2);
					trees[i][j].pop_back();
					--count;
				}
			}
		}

		// autumn
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				int sz = trees[i][j].size();
				for (int k = 0; k < sz; ++k)
				{
					const auto& tree = trees[i][j][k];
					if (tree % 5 != 0) continue;
					for (int d = 0; d < 8; ++d)
					{
						int newI = i + dx[d];
						int newJ = j + dy[d];

						if (newI < 0 || newJ < 0 || newI >= n || newJ >= n)
							continue;

						trees[newI][newJ].push_front(1);
						++count;
					}
				}
			}
		}

		// winter
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				detergent[i][j] += initialDetergent[i][j];
			}
		}
	}

	cout << count << "\n";

	return 0;
}