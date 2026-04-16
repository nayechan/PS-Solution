#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;

	vector<int> hpDrain(n), happiness(n);

	vector<int> result(100, 0);

	for(int i=0;i<n;++i)
	{
		cin >> hpDrain[i];
	}

	for(int i=0;i<n;++i)
	{
		cin >> happiness[i];
	}

	for(int i=0;i<n;++i)
	{
		for(int j=99;j>=hpDrain[i];--j)
		{
			result[j] = max(result[j], result[j - hpDrain[i]] + happiness[i]);
		}
	}

	cout << result[99] << endl;

	return 0;
}