#include <iostream>

using namespace std;

int main()
{
	int MAX;
	cin >> MAX;
	for (int i = 0; i < MAX; i++)
	{
		int result;
		int x1, y1, r1, x2, y2, r2;
		cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

		int d2 = (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
		int diff2 = (r2 - r1)*(r2 - r1);
		int sum2 = (r1 + r2)*(r1 + r2);

		if (x1 == x2 && y1 == y2 && r1 == r2) result = -1;

		else if (diff2 == d2 || sum2 == d2)
		{
			result = 1;
		}
		else if (sum2<d2||diff2>d2||d2==0)
		{
			result = 0;
		}

		else result = 2;
		cout << result << endl;
	}
	return 0;
}