#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

constexpr long long MOD = 1'000'000'007;

vector<vector<long long>> matmul(vector<vector<long long>>& a, vector<vector<long long>>& b)
{
	long long sz = a.size();
	vector<vector<long long>> result(sz, vector<long long>(sz, 0));

	for (long long i = 0; i < sz; ++i)
	{
		for (long long k = 0; k < sz; ++k)
		{
			for (long long j = 0; j < sz; ++j)
			{
				result[i][j] += (a[i][k] * b[k][j]);
				result[i][j] %= MOD;
			}

		}
	}

	return result;
}

vector<vector<long long>> matpow(vector<vector<long long>>& matrix, long long n)
{
	// n -> binary lifting
	vector<vector<vector<long long>>> matPow; // 1, 2, 4, 8, ...
	matPow.push_back(matrix);

	long long sz = matrix.size();

	vector<vector<long long>> newMatrix;
	for (long long i = 2; i <= n; i *= 2)
	{
		newMatrix = matmul(matPow.back(), matPow.back());
		matPow.push_back(newMatrix);
	}

	newMatrix.assign(sz, vector<long long>(sz, 0));
	for (long long i = 0; i < sz; ++i)
	{
		newMatrix[i][i] = 1;
	}

	long long bitPos = 0;
	while (n > 0)
	{
		if (n & 1)
			newMatrix = matmul(newMatrix, matPow[bitPos]);

		++bitPos;
		n >>= 1;
	}

	return newMatrix;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n;
	cin >> n;

	vector<vector<long long>> matrix = { 
		{0,1,1,0,0,0,0,0},
		{1,0,1,1,0,0,0,0},
		{1,1,0,1,1,0,0,0},
		{0,1,1,0,1,1,0,0},
		{0,0,1,1,0,1,0,1},
		{0,0,0,1,1,0,1,0},
		{0,0,0,0,0,1,0,1},
		{0,0,0,0,1,0,1,0}
	};

	matrix = matpow(matrix, n);

	cout << matrix[0][0] << "\n";

	return 0;
}