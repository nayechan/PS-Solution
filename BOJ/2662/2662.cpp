#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> data(m, vector<int>(n+1, 0));
	vector<vector<int>> sum(m, vector<int>(n + 1, -1));
	vector<vector<int>> count(m, vector<int>(n + 1, 0));
	
	sum[0][0] = 0;

	for (int i = 0; i < n; ++i)
	{
		int idx;
		cin >> idx;

		for (int k = 0; k < m; ++k)
		{
			cin >> data[k][idx];
		}
	}

	for (int i = 1; i <= n; ++i)
	{
		sum[0][i] = data[0][i];
		count[0][i] = i;
	}

	for (int i = 1; i < m; ++i)
	{
		for (int j = 0; j <= n; ++j)
		{
			for (int k = 0; k <= n; ++k)
			{
				if (j + k > n) continue;
				if (sum[i - 1][j] == -1) continue;

				int newSum = sum[i - 1][j] + data[i][k];

				if (sum[i][j + k] < newSum)
				{
					sum[i][j + k] = newSum;
					count[i][j + k] = k;
				}
			}
		}
	}

	cout << sum[m - 1][n] << '\n';

	vector<int> stack;

	int current = n;
	for (int i = m-1; i >= 0; --i)
	{
		stack.push_back(count[i][current]);
		current -= count[i][current];
	}

	while (!stack.empty())
	{
		cout << stack.back() << " ";
		stack.pop_back();
	}
	cout << '\n';
	return 0;
}