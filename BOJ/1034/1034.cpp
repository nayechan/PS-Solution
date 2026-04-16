#include <iostream>
#include <bitset>
#include <vector>
#include <unordered_map>

using namespace std;

int flipCount(string str)
{
	int count = 0;
	for (char ch : str)
	{
		if (ch == '0') ++count;
	}
	return count;
}

int main()
{
	int n, m;
	cin >> n >> m;

	unordered_map<string, int> count;

	for (int i = 0;i < n;++i)
	{
		string input;
		cin >> input;
		++count[input];
	}

	int _max = 0;
	int k;
	cin >> k;
	for (const auto& p : count)
	{
		int flip = flipCount(p.first);

		if (flip <= k && flip % 2 == k % 2)
			_max = _max > p.second ? _max : p.second;
	}

	cout << _max << endl;

	return 0;
}