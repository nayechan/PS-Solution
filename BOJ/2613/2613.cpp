#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<int> data(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> data[i];
	}

	int low = 1;
	int high = 100 * 300;

	while (low < high)
	{
		int g = 1;
		int mid = (low + high) / 2;

		int current = 0;
		for (const auto& e : data)
		{
			if (current + e <= mid)
			{
				current += e;
			}
			else if (e <= mid)
			{
				++g;
				current = e;
			}
			else
			{
				g = 301;
				break;
			}
		}

		if (g > m)
		{
			low = mid + 1;
		}
		else
		{
			high = mid;
		}
	}

	int current = 0;
	int count = 0;
	int index = 0;
	cout << high << '\n';
	for (const auto& e : data)
	{
		if (current + e > high || index == n - m + 1)
		{
			cout << count << " ";
			--m;
			count = 1;
			current = e;
		}
		else
		{
			current += e;
			++count;
		}
		++index;
	}

	cout << count << '\n';

	return 0;
}