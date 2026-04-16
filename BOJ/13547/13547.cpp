#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<int> data(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> data[i];
	}

	int m;
	cin >> m;

	vector<tuple<int, int, int>> queries(m);
	for (int i = 0; i < m; ++i)
	{
		int s, e;
		cin >> s >> e;
		queries[i] = { i, s - 1, e-1 };
	}

	int sqrtN = ceil(sqrt(n));

	sort(queries.begin(), queries.end(), [&sqrtN](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
		int bucketA = get<1>(a) / sqrtN;
		int bucketB = get<1>(b) / sqrtN;

		if (bucketA != bucketB)
			return bucketA < bucketB;

		return get<2>(a) < get<2>(b);
		});

	auto [currentQi, currentS, currentE] = queries[0];
	vector<int> count(1000001);
	int currentCount = 0;
	vector<int> result(m);
	
	for (int i = currentS; i <= currentE; ++i)
	{
		if (count[data[i]] == 0)
			++currentCount;
		count[data[i]]++;
	}
	result[currentQi] = currentCount;

	for (int i = 1; i < m; ++i)
	{
		auto [qi, s, e] = queries[i];
		while (currentS > s)
		{
			--currentS;
			if (count[data[currentS]] == 0)
				++currentCount;
			count[data[currentS]]++;
		}
		while (currentE < e)
		{
			++currentE;
			if (count[data[currentE]] == 0)
				++currentCount;
			count[data[currentE]]++;

		}
		while (currentS < s)
		{
			count[data[currentS]]--;
			if (count[data[currentS]] == 0)
				--currentCount;
			++currentS;
		}
		while (currentE > e)
		{
			count[data[currentE]]--;
			if (count[data[currentE]] == 0)
				--currentCount;
			--currentE;
		}

		result[qi] = currentCount;
	}

	for (int i = 0; i < m; ++i)
	{
		cout << result[i] << "\n";
	}

	return 0;
}