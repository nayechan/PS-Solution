#include <iostream>
#include <unordered_set>
#include <vector>
#include <bitset>

using namespace std;

void resolve(vector<bitset<10000>>& data, vector<int>& root, int i)
{
	if (!data[i].none()) return;

	if (root[i] == -1)
	{
		data[i].set(i);
		return;
	}

	resolve(data, root, root[i]);
	data[i] |= data[root[i]];
	data[i].set(i);
}

void test()
{
	int n;
	cin >> n;

	vector<bitset<10000>> data(n, bitset<10000>());
	vector<int> root(n, -1);
	vector<int> rank(n, 0);

	for (int i = 0; i < n-1; ++i)
	{
		int a, b;
		cin >> a >> b;
		--a; --b;
		root[b] = a;
	}

	for (int i = 0; i < n; ++i)
	{
		resolve(data, root, i);
	}

	int a, b;
	cin >> a >> b;
	--a; --b;

	bitset<10000> common = data[a] & data[b];

	int result = -1;
	int bitCount = -1;

	for (int i = 0; i < n; ++i)
	{
		if (!common.test(i)) continue;

		int currentCount = data[i].count();
		if (currentCount < bitCount) continue;
		result = i;
		bitCount = currentCount;
	}

	cout << result+1 << endl;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	for(int i=0;i<t;++i)
		test();
	return 0;
}