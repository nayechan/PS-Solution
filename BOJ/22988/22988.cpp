#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

constexpr long long INF = 987654321;

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n, x;
	cin >> n >> x;
	x *= 2;

	map<long long, long long> data;
	long long result = 0;

	for (long long i = 0; i < n; ++i)
	{
		long long amount;
		cin >> amount;

		amount *= 2;

		if (amount != x)
			data[amount]++;

		else
			result++;
	}

	while (!data.empty() && data.begin()->first < x)
	{
		long long current = data.begin()->first;

		auto target = data.lower_bound(x / 2 - current);

		if (target == data.end())
			target = data.begin();

		if (target == data.begin() && data.begin()->second < 2)
			advance(target, 1);


		if (target != data.end())
		{
			long long newCap = min(x, current + target->first + x / 2);
			//cout << current << " " << target->first << " " << newCap << endl;

			if (newCap != x)
				data[newCap]++;
			else
				result++;

			data.begin()->second--;
			target->second--;

			bool isSame = (data.begin() == target);

			if (data.begin()->second <= 0)
				data.erase(data.begin());


			if (!isSame && target->second <= 0)
				data.erase(target);
		}
		else
		{
			break;
		}
	}

	cout << result << '\n';

	return 0;
}