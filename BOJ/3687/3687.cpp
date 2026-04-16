#include <iostream>
#include <vector>

using namespace std;

int num[] = { 99, 99, 1, 7, 4, 2, 6, 8 };

void test()
{
	int n;
	cin >> n;

	int n2 = n;

	int length = ((n - 1) / 7) + 1;

	for (int i = length; i >= 1; --i)
	{
		int currentIndex = 0;
		for (int j = 2; j <= 7; ++j)
		{
			if (i == 1)
			{
				currentIndex = n;
				break;
			}

			int newIndex = j;
			int newLength = ((n - j - 1) / 7) + 1;
			if (n - j - 1 < 0) newLength = 0;

			if (newLength < i && num[currentIndex] > num[newIndex])
			{
				currentIndex = newIndex;
			}
		}

		cout << num[currentIndex];
		n -= currentIndex;
		if (i == length) num[6] -= 6;
	}

	cout << " ";

	if (n2 % 2 == 1)
	{
		cout << 7;
		n2 -= 3;
	}

	while (n2 > 0)
	{
		cout << 1;
		n2 -= 2;
	}
	cout << '\n';
	num[6] += 6;
}

int main()
{
	int t;
	cin >> t;
	for (int i = 0; i < t; ++i) test();
	return 0;
}