#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

#define N 5
#define M 15

int main() {
	string input;
	getline(cin, input);

	int token;
	stringstream ss(input);

	vector<int> data;

	while(ss >> token)
	{
		data.push_back(token);
	}

	vector<vector<int>> dp(M+1, vector<int>(M+1, -1));
	dp[0][0] = 0;

	for(int i=1;i<=N;++i)
	{
		for(int count=1;count<=M;++count)
		{
			for(int sum=i;sum<=M;++sum)
			{
				if(dp[count-1][sum-i] == -1) continue;

				dp[count][sum] = max(dp[count][sum], dp[count-1][sum-i] + data[i-1]);
			}
		}
	}

	int _max = 0;

	for(int i=1;i<=3;++i)
	{
		for(int j=1;j<=10;++j)
		{
			_max = max(_max, dp[i][j]);
		}
	}

	for(int i=4;i<=M;++i)
	{
		for(int j=1;j<=15;++j)
		{
			_max = max(_max, dp[i][j]);
		}
	}

	cout << _max << endl;

	
	return 0;
}