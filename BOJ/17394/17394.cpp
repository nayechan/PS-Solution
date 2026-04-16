#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

int get(vector<bool>& target, int n)
{
	queue<int> q;
	q.push(n);

	vector<bool> visited(1000011, false);
	int visitedCount = 0;

	int round = 0;
	while (!q.empty() && visitedCount <= 1000010)
	{
		int count = q.size();

		for (int i = 0; i < count; ++i)
		{
			int current = q.front();
			q.pop();

			if (current < 0 || current > 1000010) continue;

			if (visited[current]) continue;

			visited[current] = true;
			++visitedCount;

			if (current <= 100000)
			{
				if (target[current]) return round;
			}

			if(!visited[current/2]) q.push(current / 2);
			if (!visited[current / 3]) q.push(current / 3);
			if (current+1 <= 1000010 && !visited[current + 1]) q.push(current + 1);
			if(current != 0 && !visited[current - 1]) q.push(current - 1);
		}

		++round;
	}

	return -1;
}

void test()
{
	int n, a, b;
	cin >> n >> a >> b;

	vector<bool> target(100001, true);
	for (int i = 2; i <= 100000; ++i)
	{
		if (!target[i]) continue;
		for (int j = i * 2; j <= 100000; j += i)
		{
			target[j] = false;
		}
	}
	target[0] = false;
	target[1] = false;

	for (int i = 0; i < a; ++i)
	{
		target[i] = false;
	}
	for (int i = b + 1; i <= 100000; ++i)
	{
		target[i] = false;
	}

	int result = get(target, n);

	cout << result << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;

	for (int i = 0; i < t; ++i)
		test();
	return 0;
}