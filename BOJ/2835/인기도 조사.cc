#include <iostream>
#include <vector>

using namespace std;

constexpr long long multiplier[8] = { 36000, 3600, 0, 600, 60, 0, 10, 1 };

pair<long long, long long> getInput()
{
	char dummy;
	string start, end;
	pair<long long, long long> result = { 0,0 };
	cin >> start >> dummy >> end;

	for (long long i = 0; i < 8; ++i)
	{
		result.first += multiplier[i] * (start[i] - '0');
	}

	for (long long i = 0; i < 8; ++i)
	{
		result.second += multiplier[i] * (end[i] - '0');
	}

	if (result.second < result.first)
		result.second += 86400;

	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n;
	cin >> n;

	vector<long long> raw(86400, 0);
	vector<long long> sweep(86400, 0);
	vector<long long> sum(172801, 0);
	long long offset = 0;

	for (long long i = 0; i < n; ++i)
	{
		pair<long long, long long> input = getInput();
		raw[input.first % 86400] += 1;
		raw[(input.second + 1) % 86400] -= 1;

		if (input.first + 1 <= 86400 && 86400 <= input.second + 1)
		{
			++offset;
		}
	}

	long long current = offset;
	for (long long i = 0; i < 86400; ++i)
	{
		current += raw[i];
		sweep[i] += current;
	}

	current = 0;
	for (long long i = 0; i < 172801; ++i)
	{
		current += sweep[i%86400];
		sum[i] += current;
	}

	cin >> n;

	for (long long i = 0; i < n; ++i)
	{
		pair<long long, long long> input = getInput();
		long long result = sum[input.second];

		if (input.first > 0)
		{
			result -= sum[input.first - 1];
		}

		long double ratio = result;
		ratio /= (long double)(input.second - input.first + 1);
		
		cout.precision(10);
		cout << fixed << ratio << '\n';
	}

	return 0;
}