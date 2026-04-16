#include <iostream>
#include <vector>

using namespace std;

long long maxIndex(long long n, long long limit)
{
	long long sum = 0;
	for (long long i = 1; i <= limit; ++i)
	{
		sum += min(n / i, limit);
	}

	return sum;
}

long long bisect(long long k, long long n)
{
	long long min = 1;
	long long max = n*n;

	while (min < max)
	{
		long long mid = (min + (max - min) / 2);

		if (maxIndex(mid, n) < k)
		{
			min = mid + 1;
		}
		else
		{
			max = mid;
		}
	}

	return max;
}

int main()
{
	int n, k;
	cin >> n >> k;

	cout << bisect(k, n) << endl;

	return 0;
}