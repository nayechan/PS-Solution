#include <iostream>
#include <vector>
#include <set>

using namespace std;

void setTeam(vector<vector<int>>& data, vector<int>& team, int i)
{
	vector<int> queue;
	int count;

	if (team[i] != -1) return;
	team[i] = 0;

	queue.push_back(i);

	while (!queue.empty())
	{
		int current = queue.back();
		queue.pop_back();

		for (const auto& e : data[current])
		{
			if (team[e] == -1)
			{
				team[e] = 1 - team[current];
				queue.push_back(e);
			}
		}
	}
}

int main()
{
	int n;
	cin >> n;
	
	vector<vector<int>> data(n);
	vector<int> team(n, -1);

	for (int i = 0; i < n; ++i)
	{
		int count;
		cin >> count;

		for (int j = 0; j < count; ++j)
		{
			int input;
			cin >> input;

			data[i].push_back(input-1);
		}
	}

	for(int i=0;i<n;++i)
		setTeam(data, team, i);

	vector<int> teamA, teamB;

	for (int i = 0; i < n; ++i)
	{
		if (team[i] == 0)
			teamA.push_back(i + 1);
		else
			teamB.push_back(i + 1);
	}

	cout << teamA.size() << endl;
	for (const auto& e : teamA)
	{
		cout << e << " ";
	}
	cout << endl;
	cout << teamB.size() << endl;
	for (const auto& e : teamB)
	{
		cout << e << " ";
	}


	return 0;
}