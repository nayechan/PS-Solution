#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <climits>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<pair<long long, long long>> lines;

	for (int i = 0; i < n; ++i)
	{
		pair<long long, long long> line;
		cin >> line.first >> line.second;

		lines.push_back(line);
	}

	sort(lines.begin(), lines.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
		return a.first < b.first;
		});

	pair<long long, long long> current = { LLONG_MIN, LLONG_MIN };
	long long len = 0LL;

	for (int i = 0; i < n; ++i)
	{
		pair<long long, long long> line = lines[i];
		if (line.first <= current.second && line.second > current.second)
		{
			len += (line.second - current.second);
			current.second = line.second;
		}

		else if (line.first > current.second)
		{
			len += (line.second - line.first);
			current = line;
		}
	}

	cout << len << '\n';
	return 0;
}