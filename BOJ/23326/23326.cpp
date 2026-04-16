#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	set<int> data;
	int n, q;
	cin >> n >> q;

	for (int i = 0; i < n; ++i)
	{
		int input;
		cin >> input;
		if (input == 1)
			data.insert(i);
	}

	int pos = 0;

	for (int i = 0; i < q; ++i)
	{
		int choice;
		cin >> choice;

		if (choice == 1)
		{
			int target;
			cin >> target;
			--target;

			if (data.find(target) != data.end())
			{
				data.erase(target);
			}
			else
			{
				data.insert(target);
			}

		}
		else if (choice == 2)
		{
			int moveAmount;
			cin >> moveAmount;

			pos = (pos+moveAmount)%n;
		}
		else
		{
			if(data.empty())
			{
				cout << -1 << '\n';
				continue;
			}

			int result = -1;
			set<int>::iterator itr = data.lower_bound(pos);
			if (itr != data.end())
				result = *itr - pos;

			else
			{
				itr = data.begin();
				if(itr != data.end())
				{
					result = n-pos+*itr;
				}
			}
			
			cout << result << '\n';
		}
	}

	return 0;
}