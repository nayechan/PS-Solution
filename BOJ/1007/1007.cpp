#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

void test()
{
	int n;
	cin >> n;
	vector<pair<int, int>> pos = vector<pair<int, int>>(n);

	for (int i = 0; i < n; ++i)
	{
		cin >> pos[i].first >> pos[i].second;
	}

	vector<bool> permutation(n, false);
	for (int i = 0; i < n / 2; ++i)
	{
		permutation[i] = true;
	}

	long double result = INT_MAX;

	do {
		pair<int, int> v = { 0,0 };
		for (int i = 0; i < n; ++i)
		{
			if (permutation[i] == true)
			{
				v.first += pos[i].first;
				v.second += pos[i].second;
			}
			else
			{
				v.first -= pos[i].first;
				v.second -= pos[i].second;
			}
		}

		long double localResult = sqrt((long double)v.first * v.first + (long double)v.second * v.second);
		if (localResult < result) result = localResult;
	} while (prev_permutation(permutation.begin(), permutation.end()));
	cout << fixed;
	cout.precision(12);
	cout << result << endl;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; ++i)
		test();
	return 0;
}