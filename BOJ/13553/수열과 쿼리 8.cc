#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <set>

using namespace std;

constexpr long long MAX_N = (1 << 17);
long long fenwick[MAX_N + 1];

void update(long long idx, long long value)
{
	while (idx <= MAX_N)
	{
		fenwick[idx] += value;
		idx += idx & (-idx);
	}
}

long long query(long long idx)
{
	long long value = 0;
	while (idx)
	{
		value += fenwick[idx];
		idx &= (idx - 1);
	}

	return value;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n, k;
	cin >> n >> k;

	vector<long long> data(n);
	for (long long i = 0; i < n; ++i)
	{
		cin >> data[i];
	}

	long long m;
	cin >> m;

	vector<tuple<long long, long long, long long>> queries(m);
	for (long long i = 0; i < m; ++i)
	{
		long long s, e;
		cin >> s >> e;
		queries[i] = { i, s - 1, e - 1 };
	}

	long long sqrtN = ceil(sqrt(n));

	sort(queries.begin(), queries.end(), [&sqrtN](const tuple<long long, long long, long long>& a, const tuple<long long, long long, long long>& b) {
		long long bucketA = get<1>(a) / sqrtN;
		long long bucketB = get<1>(b) / sqrtN;

		if (bucketA != bucketB)
			return bucketA < bucketB;

		return get<2>(a) < get<2>(b);
		});

	auto [currentQi, currentS, currentE] = queries[0];
	multiset<long long> list;
	long long currentCount = 0;
	vector<long long> result(m);

	for (long long i = currentS; i <= currentE; ++i)
	{
		currentCount += query(min(data[i] + k, 100001LL)) - query(max(data[i] - k - 1, 0LL));
		update(data[i], 1);
	}
	result[currentQi] = currentCount;

	for (long long i = 1; i < m; ++i)
	{
		auto [qi, s, e] = queries[i];
		while (currentS > s)
		{
			--currentS;
			currentCount += query(min(data[currentS] + k, 100001LL)) - query(max(data[currentS] - k - 1, 0LL));
			update(data[currentS], 1);
		}
		while (currentE < e)
		{
			++currentE;
			currentCount += query(min(data[currentE] + k, 100001LL)) - query(max(data[currentE] - k - 1, 0LL));
			update(data[currentE], 1);

		}
		while (currentS < s)
		{
			update(data[currentS], -1);
			currentCount -= query(min(data[currentS] + k, 100001LL)) - query(max(data[currentS] - k - 1, 0LL));
			++currentS;
		}
		while (currentE > e)
		{
			update(data[currentE], -1);
			currentCount -= query(min(data[currentE] + k, 100001LL)) - query(max(data[currentE] - k - 1, 0LL));
			--currentE;
		}

		result[qi] = currentCount;
	}

	for (long long i = 0; i < m; ++i)
	{
		cout << result[i] << "\n";
	}

	return 0;
}