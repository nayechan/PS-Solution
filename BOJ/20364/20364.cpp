#include <iostream>
#include <vector>

using namespace std;

int getRoot(vector<int> &data, int n)
{
	if(n <= 0)
		return 0;

	int bitCount = 32 - __builtin_clz(n);

	for(int i=bitCount-1;i>=0;--i)
	{
		if(data[n>>i]!=0)
			return n>>i;
	}

	return 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int n, q; cin >> n >> q;
	vector<int> data(n+1, 0);

	for(int i=0;i<q;++i)
	{
		int _q;
		cin >> _q;

		int result = getRoot(data, _q);
		
		cout << result << '\n';

		data[_q] = 1;
	}


	return 0;
}