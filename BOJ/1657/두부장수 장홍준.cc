#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

constexpr long long INF = 1e18;

using namespace std;

void update_matching(vector<long long>& lmatch, vector<long long>& rmatch, vector<long long>& rev, long long r)
{
	while (r != -1)
	{
		long long l = rev[r];
		long long prev_r = lmatch[l];
		lmatch[l] = r;
		rmatch[r] = l;
		r = prev_r;
	}
}

void augment(vector<vector<long long>>& weight, vector<long long>& lmatch, vector<long long>& rmatch,
	vector<long long>& lh, vector<long long>& rh)
{
	long long n = weight.size();
	vector<pair<long long, long long>> slack(n, { INF, -1 });
	vector<long long> rev(n, -1);
	vector<bool> fl(n, false), fr(n, false);

	long long root = -1;
	for (long long l = 0; l < n; ++l)
	{
		if (lmatch[l] == -1) {
			root = l;
			break;
		}
	}
	if (root == -1) return;

	queue<long long> q;

	auto add_to_right = [&](long long r) {
		fr[r] = true;
		rev[r] = slack[r].second;
		if (rmatch[r] == -1) {
			update_matching(lmatch, rmatch, rev, r);
			return true;
		}
		fl[rmatch[r]] = true;
		q.push(rmatch[r]);
		return false;
		};

	q.push(root);
	fl[root] = true;

	while (true)
	{
		while (!q.empty())
		{
			long long l = q.front(); q.pop();

			for (long long r = 0; r < n; ++r)
			{
				if (fr[r]) continue;

				long long diff = lh[l] + rh[r] - weight[l][r];

				if (diff < slack[r].first)
					slack[r] = { diff, l };

				if (slack[r].first != 0) continue;
				if (add_to_right(r)) return;
			}
		}

		long long delta = INF;
		for (long long r = 0; r < n; ++r)
			if (!fr[r]) delta = min(delta, slack[r].first);

		if (delta == INF) return;

		for (long long l = 0; l < n; ++l)
			if (fl[l]) lh[l] -= delta;

		for (long long r = 0; r < n; ++r) {
			if (fr[r]) rh[r] += delta;
			else slack[r].first -= delta;
		}

		for (long long r = 0; r < n; ++r) {
			if (fr[r] || slack[r].first != 0) continue;
			if (add_to_right(r)) return;
		}
	}
}

long long hungarian(vector<vector<long long>>& weight, vector<long long>& lmatch, vector<long long>& rmatch)
{
	long long n = weight.size();
	vector<long long> lh(n, 0), rh(n, 0);

	for (long long l = 0; l < n; l++)
		lh[l] = *max_element(weight[l].begin(), weight[l].end()); //최대 가중치이므로

	for (long long i = 0; i < n; i++)
		augment(weight, lmatch, rmatch, lh, rh);

	long long result = 0;
	for (long long l = 0; l < n; l++)
	{
		if (lmatch[l] != -1) {
			result += weight[l][lmatch[l]];
		}
	}
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n, m;
	cin >> n >> m;

	vector<vector<long long>> data(n, vector<long long>(m));

	vector<pair<long long,long long>> a, b;
	for (long long i = 0; i < n; ++i)
	{
		string input;
		cin >> input;
		for (long long j = 0; j < m; ++j)
		{
			data[i][j] = input[j] - 'A';
			if ((i + j) % 2 == 0)
				a.push_back({ i,j });
			else
				b.push_back({ i,j });
		}
	}

	vector<vector<long long>> score = {
		{10,8,7,5,0,1},
		{8,6,4,3,0,1},
		{7,4,3,2,0,1},
		{5,3,2,2,0,1},
		{0,0,0,0,0,0},
		{1,1,1,1,0,0}
	};

	long long sizeA = a.size(), sizeB = b.size();
	long long N = max(sizeA, sizeB);
	vector<vector<long long>> board(N, vector<long long>(N, 0));

	for (long long i = 0; i < sizeA; ++i)
	{
		for (long long j = 0; j < sizeB; ++j)
		{
			int ax = a[i].first, ay = a[i].second;
			int bx = b[j].first, by = b[j].second;

			if (abs(ax - bx) + abs(ay - by) != 1)
			{
				board[i][j] = 0;
				continue;
			}

			board[i][j] = score[data[ax][ay]][data[bx][by]];
		}
	}
	vector<long long> lmatch(N, -1), rmatch(N, -1);

	long long result = hungarian(board, lmatch, rmatch);
	cout << result << '\n';

	return 0;
}