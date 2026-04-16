#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m, k;
	cin >> n >> m >> k;

	vector<int> data(n+1);
	vector<int> sum(n+1, 0);
	for (int i = 0; i < n; ++i)
	{
		cin >> data[i];
	}
	data[n] = 0;

	vector<int> marker(k+1);
	for (int i = 0; i < k; ++i)
	{
		cin >> marker[i];
		--marker[i];
	}
	marker[k] = n;

	int current = 0;
	for (int i = 0; i <= n; ++i)
	{
		current += data[i];
		sum[i] = current;
	}

	vector<pair<int, int>> sorted;
	for (int i = 0; i < k; ++i)
	{
		int result = 0;
		int begin = marker[i] - 1;
		int end = marker[i + 1] - 1;

		result += sum[end];
		if (begin >= 0) result -= sum[begin];

		sorted.push_back({ -result, marker[i]});
	}
	sort(sorted.begin(), sorted.end());

	vector<int> answer;
	for (int i = 0; i < m; ++i)
	{
		answer.push_back(sorted[i].second);
	}

	sort(answer.begin(), answer.end());

	for (const auto& e : answer)
	{
		cout << (e+1) << "\n";
	}
	return 0;
}