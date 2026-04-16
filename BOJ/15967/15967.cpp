#include <iostream>
#include <vector>

using namespace std;

struct segtree {
	vector<long long> tree;
	vector<long long> lazy;

	segtree(long long n){
		tree.assign(4 * n, 0);
		lazy.assign(4 * n, 0);
	}

	void build(vector<long long>& data, long long idx, long long l, long long r)
	{
		if (l == r)
		{
			tree[idx] = data[l];
			return;
		}

		long long m = (l + r) / 2;
		build(data, idx * 2, l, m);
		build(data, idx * 2 + 1, m + 1, r);

		tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
	}

	void prop(long long idx, long long s, long long e)
	{
		tree[idx] += (e - s + 1) * lazy[idx];

		if (s != e)
		{
			lazy[idx * 2] += lazy[idx];
			lazy[idx * 2 + 1] += lazy[idx];
		}
		lazy[idx] = 0;
	}

	void update(long long idx, long long s, long long e, long long l, long long r, long long v)
	{
		prop(idx, s, e);

		if (e < l || s > r) return;

		if (l <= s && e <= r)
		{
			lazy[idx] += v;
			prop(idx, s, e);
			return;
		}
		
		long long m = (s + e) / 2;
		update(idx * 2, s, m, l, r, v);
		update(idx * 2 + 1, m+1, e, l, r, v);
		tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
	}

	long long query(long long idx, long long s, long long e, long long l, long long r)
	{
		if (e < l || s > r) return 0;

		prop(idx, s, e);

		if (l <= s && e <= r)
		{
			return tree[idx];
		}

		long long m = (s + e) / 2;
		return query(idx * 2, s, m, l, r) + query(idx * 2 + 1, m + 1, e, l, r);
	}
};

int main()
{ 
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n, m, k;
	cin >> n >> m >> k;

	vector<long long> a(n);
	for (long long i = 0; i < n; ++i)
	{
		cin >> a[i];
	}

	segtree seg(4 * n);
	seg.build(a, 1, 0, n-1);

	for (long long i = 0; i < m + k; ++i)
	{
		long long op, a, b;
		cin >> op >> a >> b;
		--a; --b;

		if (op == 1)
		{
			cout << seg.query(1, 0, n - 1, a, b) << '\n';
		}
		else
		{
			long long v;
			cin >> v;

			seg.update(1, 0, n - 1, a, b, v);
		}
	}

	return 0;
}