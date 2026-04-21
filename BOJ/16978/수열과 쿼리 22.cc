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

	long long n;
	cin >> n;

	for (long long i = 1; i <= n; ++i)
	{
		long long input;
		cin >> input;

		update(i, input);
	}

	long long m;
	cin >> m;

	vector<pair<long long, long long>> updateQuery;
	vector<vector<tuple<long long, long long, long long>>> searchQuery(1);
	long long totalSearchCount = 0;

	for (long long i = 0; i < m; ++i)
	{
		long long op;
		cin >> op;

		if (op == 1)
		{
			long long a, b;
			cin >> a >> b;
			updateQuery.push_back({ a,b });
			searchQuery.push_back(vector<tuple<long long, long long, long long>>());
		}
		else if (op == 2)
		{
			long long a, b, c;
			cin >> a >> b >> c;

			searchQuery[a].push_back({ totalSearchCount++, b,c });
		}
	}

	long long updateCount = updateQuery.size();
	long long searchCount = searchQuery[0].size();

	vector<long long> searchResult(totalSearchCount);

	for (long long i = 0; i < searchCount; ++i)
	{
		auto [searchIdx, start, end] = searchQuery[0][i];
		long long result = query(end);
		if (start > 0)
			result -= query(start - 1);

		searchResult[searchIdx] = result;
	}

	for (long long i = 1; i <= updateCount; ++i)
	{
		auto [targetIdx, v] = updateQuery[i-1];
		long long current = query(targetIdx);
		if(targetIdx > 0) 
			current -= query(targetIdx - 1);
		long long diff = v - current;
		update(targetIdx, diff);

		searchCount = searchQuery[i].size();

		for (long long j = 0; j < searchCount; ++j)
		{
			auto [searchIdx, start, end] = searchQuery[i][j];
			long long result = query(end);
			if (start > 0)
				result -= query(start - 1);

			searchResult[searchIdx] = result;
		}
	}

	for (long long i = 0; i < totalSearchCount; ++i)
	{
		cout << searchResult[i] << "\n";
	}

	return 0;
}