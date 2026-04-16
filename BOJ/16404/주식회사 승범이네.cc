#include <iostream>
#include <vector>

using namespace std;

constexpr int MAX_N = (1 << 17);
int fenwick[MAX_N + 1];

void update(int idx, int value)
{
	while (idx <= MAX_N)
	{
		fenwick[idx] += value;
		idx += idx & (-idx);
	}
}

int query(int idx)
{
	int value = 0;
	while (idx)
	{
		value += fenwick[idx];
		idx &= (idx - 1);
	}

	return value;
}

int dfs(vector<vector<int>>& child, vector<int>& in, vector<int>& out, 
	int num, int idx)
{
	in[idx] = num++;
	for (const auto& e : child[idx])
	{
		num = dfs(child, in, out, num, e);
	}
	out[idx] = num - 1;
	return num;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<int> root(n+1);
	vector<vector<int>> child(n+1);
	vector<int> in(n+1), out(n+1);

	for (int i = 1; i <= n; ++i)
	{
		cin >> root[i];
		if (root[i] != -1)
			child[root[i]].push_back(i);
	}

	dfs(child, in, out, 1, 1);

	for (int i = 0; i < m; ++i)
	{
		int op;
		cin >> op;

		if (op == 1)
		{
			int a, b;
			cin >> a >> b;
			update(in[a], b);
			update(out[a] + 1, -b);
		}
		else
		{
			int a;
			cin >> a;
			cout << query(in[a]) << '\n';
		}
	}

	return 0;
}