#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

constexpr ll MAX_N = (1 << 20);
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

ll dfs(vector<vector<ll>>& child, vector<ll>& in, vector<ll>& out,
	ll num, ll idx)
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

	ll n, m;
	cin >> n >> m;

	vector<ll> root(n + 1);
	vector<vector<ll>> child(n + 1);
	vector<ll> in(n + 1), out(n + 1);

	vector<ll> initial(n + 1, 0);

	for (ll i = 1; i <= n; ++i)
	{
		cin >> initial[i];

		if(i!=1)
			cin >> root[i];

		if (root[i] != -1)
			child[root[i]].push_back(i);
	}

	dfs(child, in, out, 1, 1);

	for (ll i = 0; i < m; ++i)
	{
		char op;
		cin >> op;

		if (op == 'p')
		{
			ll a, b;
			cin >> a >> b;
			update(in[a] + 1, b);
			update(out[a] + 1, -b);
		}
		else if (op == 'u')
		{
			ll a;
			cin >> a;
			cout << query(in[a]) + initial[a] << '\n';
		}
	}

	return 0;
}