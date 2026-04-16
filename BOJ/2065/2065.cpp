#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
#include <queue>

using namespace std;

constexpr int INF = 987654321;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int m, t, n;
	cin >> m >> t >> n;

	auto comp = [](pair<int, int>& a, pair<int, int>& b) {
		return a.second > b.second;
		};
	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> left(comp), right(comp);
	vector<int> result(n);

	for (int i = 0; i < n; ++i)
	{
		int time;
		string location;
		cin >> time >> location;

		if (location == "left")
		{
			left.push({ i,time });
		}
		else
		{
			right.push({ i, time });
		}
	}

	int currentTime = 0, currentLocation = 0;

	while (true)
	{
		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)>*
			current = &left, * other = &right;

		int tA = INF, tB = INF;

		if (currentLocation == 1)
		{
			swap(current, other);
		}

		int count = 0;

		if (!current->empty()) tA = current->top().second;
		if (!other->empty()) tB = other->top().second;

		while (tA != INF && currentTime >= tA && count < m)
		{
			++count;
			result[current->top().first] = currentTime + t;
			current->pop();
			tA = current->empty() ? INF : current->top().second;
		}


		if (count > 0)
		{
			currentLocation = 1 - currentLocation;
			count = 0;
			currentTime += t;
		}

		else if (tA != INF && tA <= tB)
		{
			currentTime = current->top().second;
		}

		else if (tB != INF)
		{
			currentLocation = 1 - currentLocation;
			currentTime = max(currentTime, tB) + t;
		}

		if (tA == INF && tB == INF)
		{
			break;
		}
	}

	for (int i = 0; i < n; ++i)
	{
		cout << result[i] << '\n';
	}

	return 0;
}