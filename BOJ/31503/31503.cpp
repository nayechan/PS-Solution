#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int n, q;
	cin >> n >> q;

	vector<int> difficulty(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> difficulty[i];
	}

	deque<int> lis, lis2;
	vector<int> lisIndex(n, 1), lisIndex2(n, 1);

	for (int i = 0; i < n; ++i)
	{
		auto itr = lower_bound(lis.begin(), lis.end(), difficulty[i]);

		if (itr == lis.end())
		{
			lis.push_back(difficulty[i]);
			lisIndex[i] = lis.size() - 1;
		}

		else
		{
			int targetIndex = itr - lis.begin();

			*itr = difficulty[i];
			lisIndex[i] = targetIndex;
		}
	}

	for (int i = n-1; i >= 0; --i)
	{
		auto itr = upper_bound(lis2.begin(), lis2.end(), difficulty[i]);
		if (itr == lis2.begin()) itr = lis2.end();
		else itr = prev(itr);

		if (itr == lis2.end())
		{
			lis2.push_front(difficulty[i]);
			lisIndex2[i] = lis2.size() - 1;
		}

		else
		{
			int targetIndex = lis2.end() - itr - 1;

			*itr = difficulty[i];
			lisIndex2[i] = targetIndex;
		}
	}

	for (int i = 0; i < q; ++i)
	{
		int input;
		cin >> input;
		cout << lisIndex[input - 1] + lisIndex2[input - 1] + 1 << '\n';
	}



	return 0;
}