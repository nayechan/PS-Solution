#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int INF = 987654321;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	
	string data;
	cin >> data;

	vector<int> nodeNum(2 * n);

	vector<int> stack;
	vector<vector<int>> parent(n, vector<int>(16));
	vector<int> level(n);

	int current = 0;
	for (int i=0;i<2*n;++i)
	{
		const auto& e = data[i];
		if (e == '0')
		{
			level[current] = stack.size();
			stack.push_back(current);
			nodeNum[i] = current;

			for (int i = 0; i < 16; ++i)
			{
				parent[current][i] = stack[max(0, level[current] - (1 << i))];
			}
			++current;
		}

		else if (e == '1')
		{
			nodeNum[i] = stack.back();
			stack.pop_back();
		}
	}

	int u, v;
	cin >> u >> v;

	u = nodeNum[u-1];
	v = nodeNum[v-1];

	if (level[u] < level[v]) swap(u, v);

	int diff = level[u] - level[v];

	for (int i = 0; i < 16; ++i)
	{
		if (diff & (1 << i))
		{
			u = parent[u][i];
		}
	}

	if (u != v)
	{
		for (int i = 15; i >= 0; --i)
		{
			if (parent[u][i] != parent[v][i])
			{
				u = parent[u][i];
				v = parent[v][i];
			}
		}

		u = parent[u][0];
	}


	int resultA, resultB;

	for (int i = 0; i < 2 * n; ++i)
	{
		if (nodeNum[i] == u)
		{
			if (data[i] == '0')
			{
				resultA = i+1;
			}
			else
			{
				resultB = i+1;
			}
		}
	}

	cout << resultA << " " << resultB << '\n';

	return 0;
}