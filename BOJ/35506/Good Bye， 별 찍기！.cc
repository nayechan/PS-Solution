#include <iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < 2*n; ++j)
		{
			if (2*n-i-1 == j)
				cout << "*";
			else
				cout << " ";
		}
		cout << " ";

		for (int j = 0; j < n; ++j)
		{
			if (n - i - 1 == j)
			{
				cout << "*";
			}
			else
			{
				cout << " ";
			}
		}
		cout << " ";

		for (int j = 0; j < n; ++j)
		{
			if (i == j)
			{
				cout << "*";
			}
			else
			{
				cout << " ";
			}
		}
		cout << "\n";
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < 2 * n; ++j)
		{
			if (n - i - 1 == j)
				cout << "*";
			else
				cout << " ";
		}
		cout << " ";

		for (int j = 0; j < n; ++j)
		{
			if (i == j)
			{
				cout << "*";
			}
			else
			{
				cout << " ";
			}
		}
		cout << " ";

		for (int j = 0; j < n; ++j)
		{
			if (n - i - 1 == j)
			{
				cout << "*";
			}
			else
			{
				cout << " ";
			}
		}
		cout << "\n";
	}

	return 0;
}