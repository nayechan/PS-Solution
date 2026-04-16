#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, m;
	cin >> n >> m;
	vector<long long> data(n);

	for(int i=0;i<n;++i)
	{
		cin >> data[i];
	}

	sort(data.begin(), data.end());

	for(int i=0;i<m;++i)
	{
		long long op, value;
		cin >> op >> value;

		if(op == 1)
		{
			long long count = data.end() - lower_bound(data.begin(), data.end(), value);
			cout << count << '\n';
		}
		else if(op == 2)
		{
			long long count = data.end() - upper_bound(data.begin(), data.end(), value);
			cout << count << '\n';
		}
		else
		{
			long long value2;
			cin >> value2;
			long long count = upper_bound(data.begin(), data.end(), value2) 
				- lower_bound(data.begin(), data.end(), value);
			cout << count << '\n';
		}
	}
	return 0;
}