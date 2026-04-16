#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n;
	cin >> n;

	vector<long long> data(n);

	for (long long i = 0; i < n; ++i)
		cin >> data[i];

	vector<pair<long long,long long>> stk;

	long long result = 0;

	for (long long i = 0; i < n; ++i)
	{
		while (!stk.empty() && stk.back().first < data[i])
		{
			result += stk.back().second;
			stk.pop_back();
		}

		if (!stk.empty())
		{
			if (stk.back().first == data[i])
			{
				result += stk.back().second;
				++stk.back().second;

				if (stk.size() > 1)
					++result;
			}
			else
			{
				result++;
				stk.push_back({ data[i], 1 });
			}

		}
		else
		{
			stk.push_back({ data[i], 1 });
		}

		//cout << i << " : " << result << endl;
	}

	cout << result << endl;

	return 0;
}