#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using ll = long long;
constexpr ll INF = 987654321;

constexpr int MAX_N = (1 << 10);
int fenwick[MAX_N + 1][MAX_N + 1];

void update(int r, int c, int value)
{
	while (r <= MAX_N)
	{
		int c2 = c;
		while (c2 <= MAX_N) {
			fenwick[r][c2] += value;
			c2 += c2 & (-c2);
		}
		r += r & -r;
	}
}

int query(int r, int c)
{
	int value = 0;
	while (r > 0)
	{
		int c2 = c;
		while (c2 > 0)
		{
			value += fenwick[r][c2];
			c2 -= c2 & -c2;
		}
		r -= r & -r;
	}

	return value;
}

int get(int r1, int c1, int r2, int c2)
{
	return query(r2, c2) - query(r1 - 1, c2) - query(r2, c1 - 1) + query(r1 - 1, c1 - 1);
}

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			int input; cin >> input;
			update(i+1, j+1, input);
		}
	}

	for (int i = 0; i < m; ++i)
	{
		int op; cin >> op;

		if (op == 0)
		{
			int x, y, c;
			cin >> x >> y >> c;

			int diff = c - get(x, y, x, y);
			update(x, y, diff);
		}
		else if (op == 1)
		{
			int r1, c1, r2, c2;
			cin >> r1 >> c1 >> r2 >> c2;
			cout << get(r1, c1, r2, c2) << "\n";
		}
	}

	return 0;
}