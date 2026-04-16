#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

long long gcd(long long a, long long b)
{
	return b ? gcd(b, a % b) : a;
}

//get pair of {x,y} where ax+by=gcd(a,b)
pair<long long, long long> egcd(long long a, long long b)
{
	pair<long long, long long> result = { 0,0 };

	if (b == 0)
	{
		return { 1,0 };
	}

	pair<long long, long long> prev = egcd(b, a % b);
	return { prev.second, prev.first - (a / b) * prev.second };
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n, m;
	cin >> n >> m;

	vector<pair<long long, long long>> elevators(m);

	for (long long i = 0; i < m; ++i)
	{
		long long a, b;
		cin >> b >> a;

		elevators[i] = { a,b };
	}

	long long s, t;
	cin >> s >> t;

	if (s == t)
	{
		cout << 0 << "\n";
		return 0;
	}

	queue<long long> q;
	vector<long long> parent(m, -1);

	for (long long i = 0; i < m; ++i)
	{
		if (s >= elevators[i].second && (s - elevators[i].second) % elevators[i].first == 0)
		{
			q.push(i);
			parent[i] = i;
		}
	}

	long long result = 1;
	long long resultIdx = -1;
	bool found = false;
	while (!q.empty())
	{
		long long sz = q.size();
		for (long long i = 0; i < sz; ++i)
		{
			long long current = q.front(); q.pop();
			if (t >= elevators[current].second && (t - elevators[current].second) % elevators[current].first == 0)
			{
				found = true;
				resultIdx = current;
				break;
			}
			for (long long j = 0; j < m; ++j)
			{
				if (parent[j] != -1)
					continue;

				pair<long long, long long> a = elevators[current];
				pair<long long, long long> b = elevators[j];
				auto [x, y] = egcd(a.first, b.first);
				long long g = gcd(a.first, b.first);

				if (abs(b.second - a.second) % g == 0) {
					long long step = b.first / g;
					x = x * ((b.second - a.second) / g) % step;
					x = (x % step + step) % step;

					long long minFloor = a.second + a.first * x;
					if (minFloor < b.second || minFloor < a.second)
					{
						long long lcm = a.first / g * b.first;
						long long base = max(a.second, b.second);
						long long diff = base - minFloor;
						minFloor += lcm * ((diff + lcm - 1) / lcm);
					}
					if (minFloor >= elevators[j].second && minFloor <= n)
					{
						q.push(j);
						parent[j] = current;
					}
				}

			}
		}
		if (found)
			break;
		++result;
	}

	if (!found)
	{
		cout << -1 << "\n";
		return 0;
	}

	cout << result << "\n";

	vector<long long> order;
	while (parent[resultIdx] != resultIdx)
	{
		order.push_back(resultIdx);
		resultIdx = parent[resultIdx];
	}
	order.push_back(resultIdx);

	while (!order.empty())
	{
		cout << order.back() + 1 << "\n";
		order.pop_back();
	}

	return 0;
}