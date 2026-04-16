#include <iostream>

using namespace std;

long long f(long long x)
{
	if (x <= 1) return x;

	long long tmp = x;
	long long count = 0LL;

	while (tmp > 0)
	{
		++count;
		tmp >>= 1;
	}

	long long div = 0;
	if (count > 0)
	{
		div = 1LL << (count - 1LL);
	}

	if (div == x)
	{
		return 1LL + f(x - 1);
	}

	if (div * 2LL - 1LL == x)
	{
		return 2LL * f(x >> 1) + div;
	}

	else
	{
		return f(div) + f(x % div) + (x % div);
	}
}

int main()
{
	long long a, b;
	cin >> a >> b;

	cout << f(b) - f(a - 1) << endl;

	return 0;
}