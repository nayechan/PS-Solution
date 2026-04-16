#include <iostream>

using namespace std;

unsigned long long totalPatties[51] = { 1, };

unsigned long long burger(int n, unsigned long long x, unsigned long long totalBurgers)
{
	if (n == 0)
		return 1;

	if (x == 0)
		return 0;

	unsigned long long prevBurgers = (totalBurgers - 3) / 2;

	unsigned long long left = 1, right = prevBurgers + 2;

	if (x >= right)
	{
		return totalPatties[n - 1] + burger(n - 1, x - right, prevBurgers) + 1;
	}

	if (x == right - 1)
	{
		return burger(n - 1, x - left - 1, prevBurgers) + 1;
	}

	if (x >= left)
	{
		return burger(n - 1, x - left, prevBurgers);
	}

	return 0;
}

int main()
{
	int n;
	unsigned long long x;
	cin >> n >> x;

	unsigned long long totalBurgers = 1;
	for (int i = 0; i < n; ++i)
	{
		totalBurgers = 2 * totalBurgers + 3;
		totalPatties[i + 1] = totalPatties[i] * 2 + 1;
	}


	cout << burger(n, x-1, totalBurgers) <<  endl;


	return 0;
}