#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <numeric>

constexpr long long INF = 1e18;

using namespace std;

void update_matching(vector<long long>& lmatch, vector<long long>& rmatch,
	vector<long long>& rev, long long r)
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

void augment(vector<vector<long long>>& weight,
	vector<long long>& lmatch, vector<long long>& rmatch,
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

	auto add_to_fr = [&](long long r) {
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
				if (add_to_fr(r)) return;
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
			if (add_to_fr(r)) return;
		}
	}
}

long long hungarian(vector<vector<long long>>& weight,
	vector<long long>& lmatch, vector<long long>& rmatch,
	vector<long long>& lh, vector<long long>& rh)
{
	long long n = weight.size();

	for (long long l = 0; l < n; l++)
		lh[l] = *max_element(weight[l].begin(), weight[l].end());

	for (long long i = 0; i < n; i++)
		augment(weight, lmatch, rmatch, lh, rh);

	long long result = 0;
	for (long long l = 0; l < n; l++)
		result += weight[l][lmatch[l]];
	return result;
}

bool dfs(int i, const vector<vector<int>>& graph, vector<int>& order,
	vector<int>& match, vector<int>& visited, 
	vector<bool>& used, int round, int currentJ) {
	for (int j : graph[i]) {
		if (used[j] || j == currentJ) continue;
		if (visited[j] == round) continue;
		visited[j] = round;
		if (match[j] == -1 || 
			dfs(match[j], graph, order, match, visited, used, round, currentJ)) {
			match[j] = i;
			return true;
		}
	}
	return false;
}

int bimatch(const vector<vector<int>>& graph, vector<int>& order, 
	vector<int>& seen, vector<bool> &used,
	int n, int m, int currentI, int currentJ) {
	vector<int> match(n + m, -1);
	vector<int> visited(n + m, 0);
	int result = 0, round = 0;

	for (int i = currentI + 1; i < n; ++i) {
		int u = order[i];
		if (seen[u] == -1) continue;
		if (dfs(u, graph, order, match, visited, used, ++round, currentJ))
			++result;
	}
	return result;
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<int> a(n), b(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
		--a[i];
	}
	for (int i = 0; i < n; ++i)
	{
		cin >> b[i];
		--b[i];
	}

	vector<vector<long long>> weight(m, vector<long long>(m, 0));

	vector<int> seen(m, -1);
	for (int i = 0; i < n; ++i)
	{
		weight[a[i]][b[i]]++;
		if(seen[a[i]]==-1)
			seen[a[i]] = i;
	}

	vector<long long> lmatch(m, -1), rmatch(m, -1);
	vector<long long> lh(m, 0), rh(m, 0);

	long long result = hungarian(weight, lmatch, rmatch, lh, rh);
	//cout << n - result << '\n';

	vector<bool> used(m, false);
	vector<int> arr(m, -1);
	vector<vector<int>> graph(m); 
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			if (lh[i] + rh[j] == weight[i][j]) {
				graph[i].push_back(j);
			}
		}
	}

	vector<int> order(m);
	iota(order.begin(), order.end(), 0);
	sort(order.begin(), order.end(), [&](int x, int y) {
		if (seen[x] == -1) return false;
		if (seen[y] == -1) return true;
		return seen[x] < seen[y];
		});

	for (int i = 0; i < m; ++i)
	{
		int u = order[i];
		for (int j = 0; j < m; ++j)
		{
			int v = j;
			if (used[v]) continue;
			if (lh[u] + rh[v] != weight[u][v]) continue;

			int remaining = 0;
			for (int k = i + 1; k < m; ++k)
				if (seen[order[k]] != -1) remaining++;

			if (remaining == 0 || 
				bimatch(graph, order, seen, used, m, m, i, j) == remaining)
			{
				arr[u] = v;
				used[j] = true;
				break;
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		cout << arr[a[i]] + 1 << " ";
	}
	cout << '\n';

	return 0;
}