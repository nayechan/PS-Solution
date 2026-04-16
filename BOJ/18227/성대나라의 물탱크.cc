#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using ll = long long;

constexpr ll MAX_N = (1 << 18);
ll fenwick[MAX_N + 1];

void update(ll idx, ll value)
{
	while (idx <= MAX_N)
	{
		fenwick[idx] += value;
		idx += idx & (-idx);
	}
}

ll query(ll idx)
{
	ll value = 0;
	while (idx)
	{
		value += fenwick[idx];
		idx &= (idx - 1);
	}

	return value;
}

void dfs(vector<vector<ll>>& child, vector<ll>& in, vector<ll>& out, ll idx)
{
	ll num = 1;

	vector<pair<ll, ll>> stk;
	stk.push_back({ idx, 0 });
	in[idx] = num++;
	while (!stk.empty())
	{
		auto& [node, idx] = stk.back();
		if (idx < child[node].size()) {
			ll next = child[node][idx++];
			in[next] = num++;
			stk.push_back({ next, 0 });
		}
		else
		{
			out[node] = num - 1;
			stk.pop_back();
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ll n, m;
	cin >> n >> m;

	vector<vector<ll>> tree(n + 1);

	for (ll i = 0; i < n - 1; ++i)
	{
		ll a, b;
		cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}

	queue<ll> q;
	vector<ll> root(n + 1, -1);
	vector<ll> level(n + 1, -1);
	q.push(m);
	level[m] = 1;

	while (!q.empty())
	{
		auto current = q.front(); q.pop();
		for (const auto& e : tree[current])
		{
			if (level[e] != -1) continue;
			root[e] = current;
			level[e] = level[current] + 1;
			q.push(e);
		}
	}

	vector<vector<ll>> child(n + 1);
	vector<ll> in(n + 1), out(n + 1);

	for (ll i = 1; i <= n; ++i)
	{
		if (root[i] != -1)
			child[root[i]].push_back(i);
	}

	dfs(child, in, out, m);

	ll _q;
	cin >> _q;
	for (ll i = 0; i < _q; ++i)
	{
		ll op;
		cin >> op;

		if (op == 1)
		{
			ll a;
			cin >> a;
			update(in[a], 1);
		}
		else
		{
			ll a;
			cin >> a;

			cout << (query(out[a]) - query(in[a] - 1)) * level[a] << "\n";
		}
	}

	return 0;
}