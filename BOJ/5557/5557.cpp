#include <iostream>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<long long> data(n - 1);

	for (int i = 0; i < n-1; ++i)
	{
		cin >> data[i];
	}

	long long expected;
	cin >> expected;

	vector<long long> result(21, 0);
	result[data[0]] = 1;

	for (int i = 1; i < n - 1; ++i)
	{
		vector<long long> newResult(21, 0);
		for (int j = 0; j <= 20; ++j)
		{
			if(j - data[i] >= 0)
				newResult[j] += result[j - data[i]];
			if(j + data[i] <= 20)
				newResult[j] += result[j + data[i]];
		}

		result.swap(newResult);
	}

	cout << result[expected] << endl;

	return 0;
}