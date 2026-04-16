#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int calc(int a, int b)
{
	int result = 0;

	a %= b;
	if (a == 0) return 0;

	result += a;

	// 남은 a조각을 b - a명에게 줘야 함 (ex.  4조각을 3명에게)
	return result + calc(a, b - a);
}

int main()
{
	int a, b;
	cin >> a >> b;

	cout << calc(a, b) << endl;

	return 0;
}