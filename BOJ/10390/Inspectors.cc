#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

using ll = long long;
constexpr ll INF = 1e18;

using namespace std;

void update_matching(vector<ll>& lmatch, vector<ll>& rmatch, vector<ll>& rev, ll r)
{
	while (r != -1)
	{
		ll l = rev[r];
		ll prev_r = lmatch[l];
		lmatch[l] = r;
		rmatch[r] = l;
		r = prev_r;
	}
}

void augment(vector<vector<ll>>& weight, vector<ll>& lmatch, vector<ll>& rmatch,
	vector<ll>& lh, vector<ll>& rh)
{
	ll n = weight.size();
	vector<pair<ll, ll>> slack(n, { INF, -1 });
	vector<ll> rev(n, -1);
	vector<bool> fl(n, false), fr(n, false);

	ll root = -1;
	for (ll l = 0; l < n; ++l)
	{
		if (lmatch[l] == -1) {
			root = l;
			break;
		}
	}
	if (root == -1) return;

	queue<ll> q;

	auto add_to_right = [&](ll r) {
		fr[r] = true;
		rev[r] = slack[r].second;
		if (rmatch[r] == -1) {
			update_matching(lmatch, rmatch, rev, r);
			return true;
		}
		fl[rmatch[r]] = true;
		q.push(rmatch[r]);
		return false;
		};

	q.push(root);
	fl[root] = true;

	while (true)
	{
		while (!q.empty())
		{
			ll l = q.front(); q.pop();

			for (ll r = 0; r < n; ++r)
			{
				if (fr[r]) continue;

				ll diff = lh[l] + rh[r] - weight[l][r];

				if (diff < slack[r].first)
					slack[r] = { diff, l };

				if (slack[r].first != 0) continue;
				if (add_to_right(r)) return;
			}
		}

		ll delta = INF;
		for (ll r = 0; r < n; ++r)
			if (!fr[r]) delta = min(delta, slack[r].first);

		if (delta == INF) return;

		for (ll l = 0; l < n; ++l)
			if (fl[l]) lh[l] -= delta;

		for (ll r = 0; r < n; ++r) {
			if (fr[r]) rh[r] += delta;
			else slack[r].first -= delta;
		}

		for (ll r = 0; r < n; ++r) {
			if (fr[r] || slack[r].first != 0) continue;
			if (add_to_right(r)) return;
		}
	}
}

ll hungarian(vector<vector<ll>>& weight, vector<ll>& lmatch, vector<ll>& rmatch)
{
	ll n = weight.size();
	vector<ll> lh(n, 0), rh(n, 0);

	for (ll l = 0; l < n; l++)
		lh[l] = *max_element(weight[l].begin(), weight[l].end()); //최대 가중치이므로

	for (ll i = 0; i < n; i++)
		augment(weight, lmatch, rmatch, lh, rh);

	ll result = 0;
	for (ll l = 0; l < n; l++)
		result += weight[l][lmatch[l]];
	return result;
}

void test(ll t)
{

	ll n; cin >> n;

	vector<vector<ll>> weight(n, vector<ll>(n, -INF));
	vector<ll> lmatch(n, -1), rmatch(n, -1);

	for (ll i = 0; i < n-1; ++i)
	{
		for (ll j = i + 1; j < n; ++j)
		{
			cin >> weight[i][j];
			weight[i][j] *= -1;
			weight[j][i] = weight[i][j];
		}
	}

	ll result = hungarian(weight, lmatch, rmatch) * -1;
	cout << "Case " << t+1 << ": " << result << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ll t;
	cin >> t;

	for (ll i = 0; i < t; ++i)
	{
		test(i);
	}


	return 0;
}