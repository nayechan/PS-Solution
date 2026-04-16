#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

constexpr int INF =  1'012'345'678;
constexpr pair<int, int> DEF_PAIR = { INF, -INF };

struct segtree {
	vector<pair<int,int>> data;
	vector<pair<int,int>> lazy;

	segtree(int n)
	{
		data.resize(4 * n);
		lazy.assign(4 * n, DEF_PAIR);
	}

	void init(vector<int> &rawData, int idx, int s, int e)
	{
		if (s == e)
		{
			data[idx] = { rawData[s],rawData[e] };
			return;
		}
		int m = (s + e) / 2;
		init(rawData, idx * 2, s, m);
		init(rawData, idx * 2 + 1, m + 1, e);

		data[idx] = {
			min(data[idx * 2].first,data[idx * 2 + 1].first), 
			max(data[idx * 2].second,data[idx * 2 + 1].second)
		};
	}

	void prop(int idx, int s, int e)
	{
		if (lazy[idx] == DEF_PAIR) return;
		data[idx] = lazy[idx];
		if (s != e)
		{
			lazy[idx * 2] = lazy[idx];
			lazy[idx * 2 + 1] = lazy[idx];
		}
		lazy[idx] = DEF_PAIR;
	}

	pair<int,int> query(int idx, int s, int e, int l, int r)
	{
		prop(idx, s, e);

		if (s > r || e < l) 
			return DEF_PAIR;

		if (l <= s && e <= r)
			return data[idx];

		int m = (s + e) / 2;

		pair<int, int> lh = query(idx*2, s, m, l, r);
		pair<int, int> rh = query(idx*2+1, m + 1, e, l, r);
		return {min(lh.first, rh.first), max(lh.second, rh.second)};
	}

	void update(int idx, int s, int e, int l, int r, pair<int,int> q)
	{
		prop(idx, s, e);

		if (s > r || e < l)
			return;

		if (l <= s && e <= r)
		{
			lazy[idx] = q;
			prop(idx, s, e);
			return;
		}

		int m = (s + e) / 2;
		update(idx, s, m, l, r, q);
		update(idx, m + 1, e, l, r, q);

		data[idx] = {
			min(data[idx * 2].first,data[idx * 2 + 1].first),
			max(data[idx * 2].second,data[idx * 2 + 1].second) 
		};
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<int> raw(n);

	for (int i = 0; i < n; ++i)
	{
		cin >> raw[i];
	}

	segtree seg(n);

	seg.init(raw, 1, 0, n - 1);
	for (int i = 0; i < m; ++i)
	{
		int l, r;
		cin >> l >> r;

		--l; --r;

		auto [minV, maxV] = seg.query(1, 0, n - 1, l, r);
		cout << minV << " " << maxV << "\n";
	}

	return 0;
}