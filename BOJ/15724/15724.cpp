#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n,m;
	cin >> n >> m;

	vector<vector<long long>> data(n, vector<long long>(m));
	vector<vector<long long>> sum(n+1, vector<long long>(m+1, 0));

	for(int i=0;i<n;++i)
	{
		long long rowSum = 0;
		for(int j=0;j<m;++j)
		{
			cin >> data[i][j];
			rowSum += data[i][j];
			sum[i+1][j+1] = sum[i][j+1] + rowSum;
		}
	}

	int k;
	cin >> k;

	for(int i=0;i<k;++i)
	{
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		
		long long result = sum[x2][y2];
		result -= sum[x1-1][y2];
		result -= sum[x2][y1-1];
		result += sum[x1-1][y1-1];
	
		cout << result << '\n';
	}

	return 0;
}