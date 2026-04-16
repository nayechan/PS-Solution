#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
#define INF 987654321

using namespace std;

int simulate(vector<vector<int>>& graph, vector<int>& member, bitset<10>& status)
{
	int n = member.size();

	bitset<10> visited;
	int groupCount = 0;
	int personCount[2] = { 0, 0 };

	for (int i = 0; i < n; ++i)
	{
		if (visited.test(i)) continue;
		++groupCount;

		bool isTrue = status.test(i);
		queue<int> q;
		q.push(i);
		visited.set(i);
		personCount[isTrue] += member[i];

		while (!q.empty())
		{
			int current = q.front();
			q.pop();

			for (int v: graph[current])
			{
				if (status.test(v) != isTrue || visited.test(v)) continue;
				q.push(v);
				visited.set(v);
				personCount[isTrue] += member[v];
			}
		}
	}

	if (groupCount == 2)
	{
		return std::abs(personCount[0] - personCount[1]);
	}

	return INF;
}

int main()
{
	int n;
	cin >> n;
	vector<int> member(n);
	for (int i = 0; i < n; ++i)
		cin >> member[i];

	vector<vector<int>> graph(n);

	for (int i = 0; i < n; ++i)
	{
		int m;
		cin >> m;

		for(int j = 0; j < m; ++j)
		{
			int connection; cin >> connection;
			graph[i].push_back(connection - 1);
		}
	}

	bitset<10> status;
	int finalResult = INF;
	for (int i = 0; i < (1 << n); ++i)
	{
		status = i;
		int result = simulate(graph, member, status);
		if (finalResult > result) finalResult = result;
	}

	if (finalResult == INF) finalResult = -1;

	cout << finalResult << endl;
	return 0;
}