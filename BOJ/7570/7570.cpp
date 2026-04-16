#include <iostream>
#include <vector>
#include <deque>
#include <numeric>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<int> data(n), indice(n);

	for (int i = 0; i < n; ++i)
	{
		cin >> data[i];
		indice[data[i]-1] = i;
	}

	int maxLength = 1;
	int currentLength = 1;

	for (int i = 1; i < n; ++i)
	{
		if (indice[i - 1] < indice[i]) ++currentLength;
		else currentLength = 1;

		maxLength = max(maxLength, currentLength);
	}

	cout << n - maxLength << '\n';


	return 0;
}