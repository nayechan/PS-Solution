#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#define INF 1012345678

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> students(n, vector<int>(m+1, INF));
	vector<pair<int, pair<int, int>>> list;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			int num;
			cin >> num;

			list.push_back({ num, {i,j} });
		}
	}
	sort(list.begin(), list.end());

	int count = list.size();

	int minDiff = INF;

	vector<int> countUsed(n, 0);
	set<int> used;
	int i = 0, j = 0;

	while (true)
	{
		if (i == count || j == count) break;

		++countUsed[list[j].second.first];
		used.insert(list[j].second.first);
		while (used.size() == n)
		{
			int diff = list[j].first - list[i].first;
			if (minDiff > diff) minDiff = diff;

			--countUsed[list[i].second.first];
			if (countUsed[list[i].second.first] == 0)
			{
				used.erase(list[i].second.first);
			}

			++i;
		}
		
		++j;
	}

	cout << minDiff << endl;
	return 0;
}