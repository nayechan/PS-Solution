#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	if (n == 1)
		cout << 'B' << '\n';

	else
		cout << 'A' << '\n';

	return 0;
}