#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <tuple>

constexpr long long INF = 987654321;

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n, m;
	cin >> n >> m;

	vector <pair<tuple<long long, long long, long long>, tuple<long long, long long, long long>>> data(n);
	set<long long> setX, setY, setZ;

	for (long long i = 0; i < n; ++i)
	{
		auto& [ax, ay, az] = data[i].first;
		auto& [bx, by, bz] = data[i].second;

		cin >> ax >> ay >> az >> bx >> by >> bz;

		setX.insert(ax); setX.insert(bx);
		setY.insert(ay); setY.insert(by);
		setZ.insert(az); setZ.insert(bz);
	}

	long long sizeX = setX.size(), sizeY = setY.size(), sizeZ = setZ.size();

	vector<vector<vector<long long>>> imos(sizeX+1
		, vector<vector<long long>>(sizeY+1, vector<long long>(sizeZ+1, 0)));


	for (long long i = 0; i < n; ++i)
	{
		auto& [ax, ay, az] = data[i].first;
		auto& [bx, by, bz] = data[i].second;

		long long x1 = distance(setX.begin(), setX.find(ax));
		long long y1 = distance(setY.begin(), setY.find(ay));
		long long z1 = distance(setZ.begin(), setZ.find(az));

		long long x2 = distance(setX.begin(), setX.find(bx));
		long long y2 = distance(setY.begin(), setY.find(by));
		long long z2 = distance(setZ.begin(), setZ.find(bz));

		imos[x1][y1][z1] += 1;
		imos[x2][y1][z1] -= 1;
		imos[x1][y2][z1] -= 1;
		imos[x2][y2][z1] += 1;
		imos[x1][y1][z2] -= 1;
		imos[x2][y1][z2] += 1;
		imos[x1][y2][z2] += 1;
		imos[x2][y2][z2] -= 1;
	}

	for (long long i = 0; i < sizeY+1; ++i)
	{
		for (long long j = 0; j < sizeZ+1; ++j)
		{
			for (long long k = 1; k < sizeX+1; ++k)
			{
				imos[k][i][j] += imos[k-1][i][j];
			}
		}
	}

	for (long long i = 0; i < sizeX+1; ++i)
	{
		for (long long j = 0; j < sizeZ+1; ++j)
		{
			for (long long k = 1; k < sizeY+1; ++k)
			{
				imos[i][k][j] += imos[i][k-1][j];
			}
		}
	}

	for (long long i = 0; i < sizeX+1; ++i)
	{
		for (long long j = 0; j < sizeY+1; ++j)
		{
			for (long long k = 1; k < sizeZ+1; ++k)
			{
				imos[i][j][k] += imos[i][j][k-1];
			}
		}
	}

	vector<long long> vx(setX.begin(), setX.end());
	vector<long long> vy(setY.begin(), setY.end());
	vector<long long> vz(setZ.begin(), setZ.end());


	long long result = 0;
	for (long long i = 0; i < sizeX; ++i)
	{
		for (long long j = 0; j < sizeY; ++j)
		{
			for (long long k = 0; k < sizeZ; ++k)
			{
				if (imos[i][j][k] >= m)
				{
					long long lx = vx[i + 1] - vx[i];
					long long ly = vy[j + 1] - vy[j];
					long long lz = vz[k + 1] - vz[k];

					result += lx * ly * lz;
				}
			}
		}
	}

	cout << result << '\n';

	return 0;
}