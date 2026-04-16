#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<int> data(n);
	set<int> num;
	vector<int> count(100001, 0);
	for (int i = 0; i < n; ++i)
	{
		cin >> data[i];
		num.insert(data[i]);
		++count[data[i]];
	}

	bool isInvalid = false;

	if (n % 2 == 1)
	{
		isInvalid = true;
	}
	else
	{
		int min = *num.begin();
		int max = *num.rbegin();

		if (min == max)
		{
			isInvalid = true;
		}
		else
		{
			--count[min];
			if (count[min] == 0) num.erase(min);
			--count[max];
			if (count[max] == 0) num.erase(max);

			for (int i = min + 1; i < max; ++i)
			{
				if (count[i] < 2)
				{
					isInvalid = true;
					break;
				}

				count[i] -= 2;
				if (count[i] == 0) num.erase(i);
			}
		}
	}

	if (!isInvalid && !num.empty())
	{
		int min = *num.begin();
		int max = *num.rbegin();

		for (int i = min; i < max; ++i)
		{
			if (count[i] > count[i + 1])
			{
				isInvalid = true;
				break;
			}

			count[i + 1] -= count[i];
			count[i] = 0;
		}

		if (count[max] != 0)
			isInvalid = true;
	}

	if (isInvalid)
		cout << -1 << '\n';
	else
		cout << 1 << '\n';

	return 0;
}

//2:06~