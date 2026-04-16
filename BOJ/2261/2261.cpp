#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include <unordered_map>
#include <deque>

using namespace std;

using ll = long long;
constexpr ll INF = 2e9;

ll sqDist(const pair<ll, ll>& a, const pair<ll, ll>& b)
{
	return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

pair<ll,ll> reversedPair(const pair<ll, ll>& x)
{
	return make_pair(x.second, x.first);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ll n;
	cin >> n;

	set<pair<ll, ll>> allPoints;

	for (ll i = 0; i < n; ++i)
	{
		ll x, y;
		cin >> x >> y;
		if (allPoints.find({ x,y }) != allPoints.end())
		{
			cout << "0" << "\n";
			return 0;
		}

		allPoints.insert({ x,y });
	}

	vector<pair<ll,ll>> points(allPoints.begin(), allPoints.end());
	set<pair<ll, ll>> window;

	ll pointer = 0;

	window.insert(reversedPair(points[0]));
	window.insert(reversedPair(points[1]));
	ll maxDist = sqDist(points[0], points[1]);

	for (int i=2;i<n;++i)
	{
		pair<int, int> current = points[i];

		while (pointer < i)
		{
			ll diffX = current.first - points[pointer].first;
			if (diffX * diffX > maxDist)
			{
				window.erase(reversedPair(points[pointer]));
				++pointer;
			}
			else
			{
				break;
			}
		}

		ll dist = ceil(sqrtl(maxDist + 1e-6));
		auto itrS = window.lower_bound({ current.second - dist, -INF });
		auto itrE = window.lower_bound({ current.second + dist, INF });

		for (auto itr = itrS; itr != itrE; ++itr)
		{
			maxDist = min(maxDist, sqDist(current, reversedPair(*itr)));
		}

		window.insert(reversedPair(current));
	}

	cout << maxDist << "\n";

	return 0;
}