#include <iostream>
#include <climits>

using namespace std;

long long get(long long t)
{
	long long left = t / 2;

	return (left + (t%2)) * (left + 1);
}

int findMin(int t)
{
	int min = 0;
	int max = INT_MAX;
	int m;

	while (min < max)
	{
		m = min + (max - min) / 2;
		long long v = get(m);
		if (t <= v)
		{
			max = m;
		}
		else
		{
			min = m + 1;
		}
	}
	return min;
}

int main()
{
	int n;
	cin >> n;

	for (int i = 0; i < n; ++i)
	{
		int a, b;
		cin >> a >> b;

		int t = b - a;

		cout << findMin(t) << endl;
	}
	return 0;
}