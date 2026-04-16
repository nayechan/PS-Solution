#include <iostream>
#include <vector>

using namespace std;

struct segtree {
	vector<long long> tree;
	vector<pair<long long, long long>> lazy;

	segtree(int n)
	{
		tree.assign(n * 4, 0LL);
		lazy.assign(n * 4, {0LL,0LL});
	}
};

void build(segtree& seg, vector<long long>& data, int i, int s, int e)
{
	if (s == e)
	{
		seg.tree[i] = data[s];
		return;
	}

	int m = (s + e) / 2;
	build(seg, data, i * 2, s, m);
	build(seg, data, i * 2 + 1, m + 1, e);

	seg.tree[i] = seg.tree[i * 2] + seg.tree[i * 2 + 1];
}

void prop(segtree& seg, int i, int s, int e)
{
	if (seg.lazy[i] == make_pair(0LL, 0LL)) return;
	seg.tree[i] += seg.lazy[i].second * (e - s + 1);
	seg.tree[i] += seg.lazy[i].first * (e - s) * (e - s + 1) / 2;
	if (s != e)
	{
		int m = (s + e) / 2;
		seg.lazy[i * 2].first += seg.lazy[i].first;
		seg.lazy[i * 2].second += seg.lazy[i].second;
		seg.lazy[i * 2 + 1].first += seg.lazy[i].first;
		seg.lazy[i * 2 + 1].second += (seg.lazy[i].second + seg.lazy[i].first * (m - s + 1));
	}
	seg.lazy[i] = { 0LL,0LL };
}

void update(segtree& seg, int i, int s, int e, int l, int r, long long c, long long v)
{
	prop(seg, i, s, e);

	if (r < s || e < l) return;

	if (l <= s && e <= r)
	{
		seg.lazy[i].first += c;
		seg.lazy[i].second += v + c * (s - l);
		prop(seg, i, s, e);
		return;
	}

	int m = (s + e) / 2;
	update(seg, i * 2, s, m, l, r, c, v);
	update(seg, i * 2 + 1, m + 1, e, l, r, c, v);
	seg.tree[i] = seg.tree[i * 2] + seg.tree[i * 2 + 1];
}

long long query(segtree& seg, int i, int s, int e, int l, int r)
{
	prop(seg, i, s, e);

	if (r < s || e < l) return 0;

	if (l <= s && e <= r) return seg.tree[i];

	int m = (s + e) / 2;
	return query(seg, i * 2, s, m, l, r) + query(seg, i * 2 + 1, m + 1, e, l, r);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	segtree seg(n);
	vector<long long> data(n);

	for (int i = 0; i < n; ++i)
	{
		cin >> data[i];
	}

	build(seg, data, 1, 0, n - 1);

	int m;
	cin >> m;

	for (int i = 0; i < m; ++i)
	{
		int op;
		cin >> op;

		if (op == 1)
		{
			int l, r;
			cin >> l >> r;
			--l; --r;
			update(seg, 1, 0, n - 1, l, r, 1, 1);
		}
		else
		{
			int q;
			cin >> q;
			--q;
			cout << query(seg, 1, 0, n - 1, q, q) << '\n';
		}
	}

	return 0;
}