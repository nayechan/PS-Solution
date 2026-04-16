#include <iostream>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cout.tie(0);

	int n;
	cin >> n;

	cout << 2000 << '\n';

	for (int i = 0; i < 1000; ++i)
		cout << "1 ";
	for (int i = 0; i < 1000; ++i)
		cout << "1000 ";

	return 0;
}