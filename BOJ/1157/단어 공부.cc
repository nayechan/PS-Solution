#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

constexpr long long INF = 1e18;

int main() {
	unordered_map<char, int> count;
	string str; cin >> str;
	for(auto ch : str)
	{
		count[toupper(ch)]++;
	}
	int _max = -1;
	char _ch = 0;
	for (auto [ch, c] : count)
	{
		if (_max < c)
		{
			_max = c;
			_ch = ch;
		}
		else if (_max == c)
		{
			_ch = '?';
		}
	}

	cout << _ch << "\n";

	return 0;
}