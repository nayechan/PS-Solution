#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

constexpr int dx[3] = { 0,-1,0 };
constexpr int dy[3] = { -1,0,1 }; 

pair<int, int> getPos(vector<vector<int>>& data, const pair<int, int>& pos, int d)
{
	int n = data.size();
	int m = data[0].size();
	vector<vector<bool>> visited(n, vector<bool>(m, false));


	queue<pair<int, int>> q;
	q.push(pos);

	int dist = 0;
	while (!q.empty())
	{
		int count = q.size();
		for (int c = 0; c < count; ++c)
		{
			pair<int, int> current = q.front();
			q.pop();

			for (int i = 0; i < 3; ++i)
			{
				pair<int, int> target = { current.first + dx[i], current.second + dy[i] };

				if (target.first < 0 || target.first >= pos.first) continue;
				if (target.second < 0 || target.second >= m) continue;
				if (visited[target.first][target.second]) continue;
				if (data[target.first][target.second])
				{
					return target;
				}

				visited[target.first][target.second] = true;
				q.push(target);
			}
		}
		++dist;

		if (dist == d) break;
	}

	return { -1, -1 };
}

int rowCount(vector<vector<int>>& data, int row)
{
	int m = data[0].size();

	int count = 0;
	for(int i=0;i<m;++i)
	{
		if (data[row][i] == 1) ++count;
	}

	return count;
}

int simulate(vector<vector<int>> data, vector<bool>& combination, int d)
{

	int n = data.size();
	int m = data[0].size();

	int result = 0;

	vector<pair<int,int>> removeList;
	for (int i = n - 1; i >= 0; --i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (!combination[j]) continue;

			pair<int, int> result = getPos(data, make_pair(i+1, j), d);

			if(result.first != -1)
				removeList.push_back(result);
		}

		while (!removeList.empty())
		{
			const auto& removeTarget = removeList.back();
			removeList.pop_back();

			if (data[removeTarget.first][removeTarget.second] == true)
			{
				++result;
				data[removeTarget.first][removeTarget.second] = false;
			}
		}
	}
	return result;
}

int main()
{
	int n, m, d;
	cin >> n >> m >> d;

	vector<bool> combination(m, 0);
	for (int i = m-3; i < m; ++i)
		combination[i] = 1;

	vector<vector<int>> data(n, vector<int>(m));

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cin >> data[i][j];
		}
	}

	int result = 0;

	do
	{
		int count = simulate(data, combination, d);
		result = max(count, result);
	} while (next_permutation(combination.begin(), combination.end()));

	cout << result << endl;

	return 0;
}