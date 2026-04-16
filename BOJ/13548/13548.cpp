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
	vector<int> count(100001), freq(100001);
	vector<int> result(m);

	int currentFreq = 0;
	
	for (int i = currentS; i <= currentE; ++i)
	{
		if (count[data[i]] != 0)
			freq[count[data[i]]]--;
		count[data[i]]++;
		freq[count[data[i]]]++;
		if (freq[count[data[i]]] == 1)
			currentFreq = max(currentFreq, count[data[i]]);
	}
	result[currentQi] = currentFreq;

	for (int i = 1; i < m; ++i)
	{
		auto [qi, s, e] = queries[i];
		while (currentS > s)
		{
			--currentS;
			if(count[data[currentS]] != 0)
				freq[count[data[currentS]]]--;
			count[data[currentS]]++;
			freq[count[data[currentS]]]++;
			if (freq[count[data[currentS]]] == 1 && currentFreq == count[data[currentS]] - 1)
				currentFreq++;
		}
		while (currentE < e)
		{
			++currentE;
			if (count[data[currentE]] != 0)
				freq[count[data[currentE]]]--;
			count[data[currentE]]++;
			freq[count[data[currentE]]]++;
			if (freq[count[data[currentE]]] == 1 && currentFreq == count[data[currentE]] - 1)
				currentFreq++;

		}
		while (currentS < s)
		{
			if (count[data[currentS]] != 0)
				freq[count[data[currentS]]]--;
			if (freq[count[data[currentS]]] == 0 && currentFreq == count[data[currentS]])
				--currentFreq;
			count[data[currentS]]--;
			freq[count[data[currentS]]]++;
			++currentS;
		}
		while (currentE > e)
		{
			if (count[data[currentE]] != 0)
				freq[count[data[currentE]]]--;
			if (freq[count[data[currentE]]] == 0 && currentFreq == count[data[currentE]])
				--currentFreq;
			count[data[currentE]]--;
			freq[count[data[currentE]]]++;
			--currentE;
		}

		result[qi] = currentFreq;
	}

	for (int i = 0; i < m; ++i)
	{
		cout << result[i] << "\n";
	}

	return 0;
}