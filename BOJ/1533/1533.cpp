#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

constexpr long long MOD = 1000003;

vector<vector<long long>> matmul(vector<vector<long long>>& a, vector<vector<long long>>& b)
{
	int sz = a.size();
	vector<vector<long long>> result(sz, vector<long long>(sz, 0));

	for (int i = 0; i < sz; ++i)
	{
		for (int k = 0; k < sz; ++k)
		{
			for (int j = 0; j < sz; ++j)
			{
				result[i][j] += (a[i][k] * b[k][j]);
				result[i][j] %= MOD;
			}

		}
	}

	return result;
}

vector<vector<long long>> matpow(vector<vector<long long>>& matrix, int n)
{
	// n -> binary lifting
	vector<vector<vector<long long>>> matPow; // 1, 2, 4, 8, ...
	matPow.push_back(matrix);

	int sz = matrix.size();

	vector<vector<long long>> newMatrix;
	for (int i = 2; i <= n; i *= 2)
	{
		newMatrix = matmul(matPow.back(), matPow.back());
		matPow.push_back(newMatrix);
	}

	newMatrix.assign(sz, vector<long long>(sz, 0));
	for (int i = 0; i < sz; ++i)
	{
		newMatrix[i][i] = 1;
	}

	int bitPos = 0;
	while (n > 0)
	{
		if(n & 1)
			newMatrix = matmul(newMatrix, matPow[bitPos]);

		++bitPos;
		n>>=1;
	}

	return newMatrix;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, s, e, t;

	cin >> n >> s >> e >> t;

	vector<vector<long long>> matrix(n * 9, vector<long long>(n * 9, 0));

	for (int i = 0; i < n; ++i)
	{
		string str;
		cin >> str;
		for (int j = 0; j < n; ++j)
		{
			int input = str[j];

			input -= '0';

			if (input != 0)
				matrix[i * 9][j * 9 + input - 1] = 1;
		}
	}

	for (int i = 0; i < n; ++i)
	{
		for (int k = 1; k < 9; ++k)
		{
			matrix[i * 9 + k][i * 9 + k - 1] = 1;
		}
	}

	matrix = matpow(matrix, t);

	--s; --e;

	cout << matrix[s * 9][e * 9] << "\n";

	return 0;
}