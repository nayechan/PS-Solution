#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

constexpr long long INF = 1e17;

using namespace std;

pair<long long,long long> dfs1(vector<vector<long long>>& tree, vector<vector<long long>>& weight,
	vector<long long>& sub, vector<long long>& down, long long v, long long prev = -1)
{
	long long count = tree[v].size();
	long long totalCount = 0, totalDist = 0;

	for (long long i = 0; i < count; ++i)
	{
		if (tree[v][i] == prev) continue;
		++totalCount;
		auto [subCount, subDist] =
			dfs1(tree, weight, sub, down, tree[v][i], v);

		// 거리보정이 추가되어야 함
		totalDist += (weight[v][i] * (subCount + 1) + subDist);

		totalCount += subCount;
	}

	sub[v] = totalCount;
	down[v] = totalDist;
	return { sub[v], down[v] };
}

void dfs2(vector<vector<long long>>& tree, vector<vector<long long>>& weight,
	vector<long long>& sub, vector<long long>& up, vector<long long>& down, long long v,
	long long prev = -1, long long prevWeight = 0)
{
	long long count = tree[v].size();
	long long n = tree.size();

	if (prev != -1)
	{
		up[v] = up[prev]; // 부모 가중치 가져오기
		up[v] += (down[prev] - down[v]); // 거기서 v 방향 가중치는 빼기
		up[v] -= prevWeight * (sub[v] + 1); // 이전 거리 보정 리셋
		up[v] += (n - sub[v] - 1) * prevWeight; // 멀어진 만큼 거리 보정
	}

	for (long long i = 0; i < count; ++i)
	{
		if (tree[v][i] == prev) continue;
		dfs2(tree, weight, sub, up, down, tree[v][i], v, weight[v][i]);
	}
}

void rerooting(vector<vector<long long>>& tree, vector<vector<long long>>& weight,
	vector<long long>& sub, vector<long long>& up, vector<long long>& down)
{
	dfs1(tree, weight, sub, down, 0);
	dfs2(tree, weight, sub, up, down, 0);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n;
	cin >> n;

	vector<vector<long long>> treeA(n);
	vector<vector<long long>> weightA(n);

	for (long long i = 0; i < n-1; ++i)
	{
		long long a, b, c;
		cin >> a >> b >> c;
		--a; --b;

		treeA[a].push_back(b);
		weightA[a].push_back(c);

		treeA[b].push_back(a);
		weightA[b].push_back(c);
	}

	long long m;
	cin >> m;

	vector<vector<long long>> treeB(m);
	vector<vector<long long>> weightB(m);

	for (long long i = 0; i < m - 1; ++i)
	{
		long long a, b, c;
		cin >> a >> b >> c;
		--a; --b;

		treeB[a].push_back(b);
		weightB[a].push_back(c);

		treeB[b].push_back(a);
		weightB[b].push_back(c);
	}

	vector<long long> subA(n), upA(n), downA(n);
	vector<long long> subB(m), upB(m), downB(m);
	
	rerooting(treeA, weightA, subA, upA, downA);
	rerooting(treeB, weightB, subB, upB, downB);

	long long minA = INF, minB = INF;
	long long aIdx = -1, bIdx = -1;



	for (long long i = 0; i < n; ++i)
	{
		if (minA > upA[i] + downA[i])
		{
			aIdx = i;
			minA = min(minA, upA[i] + downA[i]);
		}
	}

	for (long long i = 0; i < m; ++i)
	{
		if (minB > upB[i] + downB[i])
		{
			bIdx = i;
			minB = min(minB, upB[i] + downB[i]);
		}
	}
	
	cout << aIdx+1 << " " << bIdx+1 << '\n';
	cout << m*minA + n*minB + (n * m) << '\n';

	return 0;
}