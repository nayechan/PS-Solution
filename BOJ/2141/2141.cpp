#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>
#include <optional>

using namespace std;


pair<long long, long long> dist(vector<pair<long long, long long>>& data, long long pos)
{
	pair<long long, long long> result = { 0,0 };
	for (pair<long long,long long>& d : data)
	{
		result.second += llabs(d.first - pos) * d.second;
		if (result.second >= 1'000'000'000)
		{
			result.first += (result.second / 1'000'000'000);
			result.second = (result.second % 1'000'000'000);
		}
	}
	return result;
}

long long bisect(vector<pair<long long, long long>>& data, long long l, long long r)
{
	while (l+1 < r)
	{
		long long m = (l + r) / 2;
		pair<long long, long long> lV = dist(data, m);
		pair<long long, long long> rV = dist(data, m + 1);

		if (lV <=  rV) {
			r = m;
		}
		else
		{
			l = m;
		}
	}

	pair<long long, long long> lV = dist(data, l);
	pair<long long, long long> rV = dist(data, r);

	if (lV < rV) return l;
	if (lV == rV && l < r) return l;

	return r;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n;
	cin >> n;
	vector<pair<long long, long long>> data(n);

	for (long long i = 0;i < n;++i)
	{
		cin >> data[i].first >> data[i].second;
	}

	sort(data.begin(), data.end());

	auto result = bisect(data, data[0].first, data[n - 1].first);

	cout << result << endl;

	return 0;
}