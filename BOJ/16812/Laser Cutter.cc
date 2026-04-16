#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <cmath>

constexpr long double INF = 1e18;
constexpr long double EPS = 1e-8;

using namespace std;

void update_matching(vector<long long>& lmatch, vector<long long>& rmatch,
	vector<long long>& rev, long long r)
{
	while (r != -1)
	{
		long long l = rev[r];
		long long prev_r = lmatch[l];
		lmatch[l] = r;
		rmatch[r] = l;
		r = prev_r;
	}
}

void augment(vector<vector<long double>>& weight,
	vector<long long>& lmatch, vector<long long>& rmatch,
	vector<long double>& lh, vector<long double>& rh)
{
	long long n = weight.size();
	vector<pair<long double, long long>> slack(n, { INF, -1 });
	vector<long long> rev(n, -1);
	vector<bool> fl(n, false), fr(n, false);

	long long root = -1;
	for (long long l = 0; l < n; ++l)
	{
		if (lmatch[l] == -1) {
			root = l;
			break;
		}
	}
	if (root == -1) return;

	queue<long long> q;

	auto add_to_fr = [&](long long r) {
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
			long long l = q.front(); q.pop();

			for (long long r = 0; r < n; ++r)
			{
				if (fr[r]) continue;

				long double diff = lh[l] + rh[r] - weight[l][r];

				if (diff < slack[r].first - EPS)
					slack[r] = { diff, l };

				if (slack[r].first > EPS) continue;
				if (add_to_fr(r)) return;
			}
		}

		long double delta = INF;
		for (long long r = 0; r < n; ++r)
			if (!fr[r]) delta = min(delta, slack[r].first);

		if (delta > INF / 2.0l) return;

		for (long long l = 0; l < n; ++l)
			if (fl[l]) lh[l] -= delta;

		for (long long r = 0; r < n; ++r) {
			if (fr[r]) rh[r] += delta;
			else slack[r].first -= delta;
		}

		for (long long r = 0; r < n; ++r) {
			if (fr[r] || slack[r].first > EPS) continue;
			if (add_to_fr(r)) return;
		}
	}
}

long double hungarian(vector<vector<long double>>& weight,
	vector<long long>& lmatch, vector<long long>& rmatch)
{
	long long n = weight.size();
	vector<long double> lh(n, 0), rh(n, 0);

	for (long long l = 0; l < n; l++)
		lh[l] = *max_element(weight[l].begin(), weight[l].end());

	for (long long i = 0; i < n; i++)
		augment(weight, lmatch, rmatch, lh, rh);

	long double result = 0;
	for (long long l = 0; l < n; l++)
		result += weight[l][lmatch[l]];
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n; cin >> n;

	pair<long long, long long> start;
	cin >> start.first >> start.second;

	vector<pair<long long, long long>> s, e;

	for(int i=0;i<n;++i)
	{
		long long ax, ay, bx, by;
		cin >> ax >> ay >> bx >> by;

		s.push_back({ ax,ay });
		e.push_back({ bx,by });
	}

	vector<pair<long long, long long>> divS, divE;

	for (int i = 0; i < n; ++i)
	{
		long long dx1 = s[i].first - start.first;
		long long dy1 = s[i].second - start.second;

		long long dx2 = start.first - e[i].first;
		long long dy2 = start.second - e[i].second;

		divS.push_back(s[i]);
		divE.push_back(e[i]);


		if (dx1 * dy2 != dx2 * dy1)
		{
			continue;
		}

		long long psx = min(s[i].first, e[i].first);
		long long pex = max(s[i].first, e[i].first);
		long long psy = min(s[i].second, e[i].second);
		long long pey = max(s[i].second, e[i].second);

		if (psx <= start.first && start.first <= pex &&
			psy <= start.second && start.second <= pey)
		{
			if ((start.first == s[i].first && start.second == s[i].second) ||
				(start.first == e[i].first && start.second == e[i].second))
			{
				continue;
			}

			pair<long long, long long> mid = pair<long long, long long>(start);

			divE.back() = mid;
			divS.push_back(mid);
			divE.push_back(e[i]);
		}
	}

	int m = divS.size();
	vector<vector<long double>> weight(m, vector<long double>(m, -INF));

	vector<long long> lmatch(m, -1), rmatch(m, -1);

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			long long dx = (divE[i].first - divS[j].first);
			long long dy = (divE[i].second - divS[j].second);

			long long sqDist = dx * dx + dy * dy;

			weight[i][j] = -sqrtl(sqDist);
		}
	}

	long double result = hungarian(weight, lmatch, rmatch) * -1;

	for(int i=0;i<m;++i)
	{
		result -= (weight[i][i]);
	}
	
	cout.precision(12);
	cout << fixed << result << '\n';

	return 0;
}