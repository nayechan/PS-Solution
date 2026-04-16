#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

constexpr long long INF = 1012345678;

struct segtree {
	vector<pair<int, int>> tree;
	vector<int> lazy;
	segtree(int n)
	{
		tree.assign(4 * n, { INF,INF });
		lazy.assign(4 * n, INF);
	}

	void init(vector<int>& data, int s, int e, int idx = 1)
	{
		if (s == e)
		{
			tree[idx] = { data[s], s };
			return;
		}

		int m = (s + e) / 2;
		init(data, s, m, idx*2);
		init(data, m + 1, e, idx*2+1);
		tree[idx] = min(tree[idx*2], tree[idx*2+1]);
	}

	void prop(int s, int e, int idx)
	{
		if (lazy[idx] == INF) return;

		tree[idx] = { lazy[idx], s };
		if (s != e)
		{
			lazy[idx * 2] = lazy[idx];
			lazy[idx * 2 + 1] = lazy[idx];
		}
		lazy[idx] = INF;
	}

	void update(int l, int r, int s, int e, int v, int idx = 1)
	{
		prop(s, e, idx);

		if (s > r || e < l)
		{
			return;
		}

		if (l <= s && e <= r)
		{
			lazy[idx] = v;
			prop(s, e, idx);
			return;
		}

		int m = (s + e) / 2;
		update(l, r, s, m, v, idx * 2);
		update(l, r, m+1, e, v, idx * 2 + 1);
		tree[idx] = min(tree[idx * 2], tree[idx * 2 + 1]);
	}

	pair<int,int> query(int l, int r, int s, int e, int idx = 1)
	{
		prop(s, e, idx);

		if (s > r || e < l)
		{
			return { INF,INF };
		}

		if (l <= s && e <= r)
		{
			return tree[idx];
		}

		int m = (s + e) / 2;

		return min(query(l, r, s, m, idx * 2), query(l, r, m + 1, e, idx * 2 + 1));
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<int> data(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> data[i];
	}

	segtree seg(n);

	seg.init(data, 0, n - 1);

	int m;
	cin >> m;

	for (int i = 0; i < m; ++i)
	{
		int op;
		cin >> op;

		if (op == 1)
		{
			int idx, v;
			cin >> idx >> v;
			--idx;
			seg.update(idx, idx, 0, n - 1, v);
		}
		else
		{
			int i, j;
			cin >> i >> j;
			--i; --j;

			auto result = seg.query(i, j, 0, n - 1);
			cout << result.second+1 << "\n";
		}
	}



	return 0;
}