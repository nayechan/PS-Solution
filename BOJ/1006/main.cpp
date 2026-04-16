#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

#define INT_MAX 2147483647

using namespace std;

void test()
{
	int n, w;

	cin >> n >> w;

	vector<vector<int>> data(2, vector<int>(n));

	for (int i = 0;i < 2;++i)
	{
		for (int j = 0;j < n;++j)
		{
			cin >> data[i][j];
		}
	}

	if (n == 1)
	{
		if (data[0][0] + data[1][0] <= w) cout << "1" << endl;
		else cout << "2" << endl;
		return;
	}

	vector<vector<int>> minArmy(5, vector<int>(n));
	vector<int> cost = { 2, 1, 1, 1, 0 };
	vector<vector<int>> targetIndex = {
		{0,1,2,3,4},
		{0,1,2,3,4},
		{0,3},
		{0,2},
		{0}
	};
	vector<function<bool(int)>> isAvailable = {
		[w, data, minArmy](int index) {
			return data[0][index] <= w && data[1][index] <= w;
		},

		[w, data, minArmy](int index) {
			return data[0][index] + data[1][index] <= w;
		},

		[n, w, data, minArmy](int index) {
			int prevIndex = index - 1;
			if (prevIndex < 0) prevIndex += n;

			return data[0][prevIndex] + data[0][index] <= w && data[1][index] <= w;
		},

		[n, w, data, minArmy](int index) {
			int prevIndex = index - 1;
			if (prevIndex < 0) prevIndex += n;

			return data[1][prevIndex] + data[1][index] <= w && data[0][index] <= w;
		},

		[n, w, data, minArmy](int index) {
			int prevIndex = index - 1;
			if (prevIndex < 0) prevIndex += n;

			return data[0][prevIndex] + data[0][index] <= w && data[1][prevIndex] + data[1][index] <= w;
		}
	};

	int min = INT_MAX;
	for (int currentOperation = 0; currentOperation < 5; ++currentOperation)
	{
		if (!isAvailable[currentOperation](0))
			continue;

		for (int i = 0; i < 5; ++i)
		{
			if (currentOperation == i)
				minArmy[i][0] = cost[currentOperation];
			else
				minArmy[i][0] = INT_MAX;
		}

		for (int i = 1; i < n-1; ++i)
		{
			for (int operation = 0; operation < 5; ++operation)
			{
				if (isAvailable[operation](i))
				{
					vector<int> minList;

					for (auto&& target : targetIndex[operation])
					{
						minList.push_back(minArmy[target][i-1]);
					}

					auto min = *min_element(minList.begin(), minList.end());

					if (min == INT_MAX)
					{
						minArmy[operation][i] = INT_MAX;
					}
					else
					{
						minArmy[operation][i] = min + cost[operation];
					}
					
				}
				else
				{
					minArmy[operation][i] = INT_MAX;
				}
			}
		}

		for (int operation = 0; operation < 5; ++operation)
		{
			vector<int> availableOperation = targetIndex[currentOperation];
			auto findResult = find(availableOperation.begin(), availableOperation.end(), operation);
			if (isAvailable[operation](n-1) && findResult != availableOperation.end())
			{
				vector<int> minList;

				for (auto&& target : targetIndex[operation])
				{
					minList.push_back(minArmy[target][n - 2]);
				}

				auto min = *min_element(minList.begin(), minList.end());

				if (min == INT_MAX)
				{
					minArmy[operation][n-1] = INT_MAX;
				}
				else
				{
					minArmy[operation][n-1] = min + cost[operation];
				}
			}
			else
			{
				minArmy[operation][n - 1] = INT_MAX;
			}
		}

		for (int i = 0;i < 5;++i)
		{
			if (min > minArmy[i][n - 1])
				min = minArmy[i][n - 1];
		}
	}

	cout << min << endl;
}

int main()
{
	ios::sync_with_stdio(false);
	int t;

	cin >> t;

	for (int i = 0;i < t;++i)
	{
		test();
	}


	return 0;
}