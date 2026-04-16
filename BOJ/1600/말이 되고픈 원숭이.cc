#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <tuple>
using namespace std;

constexpr int dx[12] = {1, 2, 2, 1, -1, -2, -2, -1, 0, 0, 1, -1};
constexpr int dy[12] = {-2, -1, 1, 2, 2, 1, -1, -2, 1, -1, 0, 0};

bool isValid(vector<vector<int>>& data, vector<vector<vector<int>>>& dist, const tuple<int, int, int>& p, int w, int h, int k)
{
	const auto &[i, j, _k] = p;
	if (i < 0 || i >= w || j < 0 || j >= h || _k < 0 || _k > k)
		return false;

	if (data[i][j] == 1 || dist[i][j][_k] != -1)
		return false;

	return true;
}

void bfs(vector<vector<int>>& data, vector<vector<vector<int>>>& dist, int k)
{
	int w = data.size();
	int h = data[0].size();

	queue<tuple<int,int,int>> q;

	q.push({ 0,0,0 });

	int currentDist = 0;

	while (!q.empty())
	{
		int count = q.size();
		//cout << currentDist << " |";
		for (int i = 0; i < count; ++i)
		{
			const auto [cI, cJ, cK] = q.front();
			q.pop();

			//cout << cI << ", " << cJ << ", " << cK << "|";

			for (int j = 0; j < 8; ++j)
			{
				tuple<int, int, int> nextP = { cI + dx[j], cJ + dy[j], cK + 1 };
				if (isValid(data, dist, nextP, w, h, k))
				{
					dist[get<0>(nextP)][get<1>(nextP)][get<2>(nextP)] = currentDist + 1;
					q.push(nextP);
				}
			}
			for (int j = 8; j < 12; ++j)
			{
				tuple<int, int, int> nextP = { cI + dx[j], cJ + dy[j], cK };
				if (isValid(data, dist, nextP, w, h, k))
				{
					dist[get<0>(nextP)][get<1>(nextP)][get<2>(nextP)] = currentDist + 1;
					q.push(nextP);
				}
			}
		}
		//cout << endl;
		++currentDist;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int k;
	cin >> k;

	int w, h;
	cin >> w >> h;

	vector<vector<int>> data(w, vector<int>(h));
	vector<vector<vector<int>>> dist(w, vector<vector<int>>(h, vector<int>(k+1, -1)));

	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			cin >> data[j][i];
		}
	}

	dist[0][0][0] = 0;

	bfs(data, dist, k);

	int result = INT_MAX;

	for (int i = 0; i <= k; ++i)
	{
		if (dist[w - 1][h - 1][i] != -1)
		{
			result = min(result, dist[w - 1][h - 1][i]);
		}
	}
	if (result == INT_MAX) result = -1;
	cout << result << endl;
	return 0;
}