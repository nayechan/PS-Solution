#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <array>

constexpr long long INF = 1e18;

using namespace std;

template <int T>
struct BigWeight {
	array<long long, T> data{};

	bool operator<(const BigWeight& other) const {
		for (int i = 0; i < T; ++i)
		{
			if (other.data[i] != data[i])
				return data[i] < other.data[i];
		}

		return false;
	}

	bool operator==(const BigWeight& other) const {
		for (int i = 0; i < T; ++i)
		{
			if (other.data[i] != data[i])
				return false;
		}

		return true;
	}

	void operator+=(const BigWeight& other) {
		for (int i = T - 1; i >= 0; --i)
		{
			data[i] += other.data[i];
			if (data[i] >= (1LL << 60) && i != 0)
			{
				data[i - 1] += (data[i] >> 60);
				data[i] &= ((1LL << 60) - 1);
			}

		}
	}

	void operator-=(const BigWeight& other) {
		for (int i = T - 1; i >= 0; --i)
		{
			data[i] -= other.data[i];
			if (data[i] < 0 && i != 0)
			{
				data[i - 1] -= 1;
				data[i] += (1LL << 60);
			}

		}
	}

	bool empty()
	{
		for (int i = 0; i < T; ++i)
		{
			if (data[i] != 0) return false;
		}
		return true;
	}
};

constexpr BigWeight<6> WeightINF = { (1LL << 60) - 1, (1LL << 60) - 1 ,(1LL << 60) - 1 ,(1LL << 60) - 1 ,(1LL << 60) - 1 ,(1LL << 60) - 1 };
constexpr BigWeight<6> WeightZero = { 0,0,0,0,0,0 };

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

void augment(vector<vector<BigWeight<6>>>& weight,
	vector<long long>& lmatch, vector<long long>& rmatch,
	vector<BigWeight<6>>& lh, vector<BigWeight<6>>& rh)
{
	long long n = weight.size();
	vector<pair<BigWeight<6>, long long>> slack(n, { WeightINF, -1});
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

	BigWeight<6> diff;

	while (true)
	{
		while (!q.empty())
		{
			long long l = q.front(); q.pop();

			for (long long r = 0; r < n; ++r)
			{
				if (fr[r]) continue;

				diff = { 0,0,0,0,0,0 };

				diff += lh[l];
				diff += rh[r];
				diff -= weight[l][r];

				if (diff < slack[r].first)
					slack[r] = { diff, l };

				if (!(slack[r].first == WeightZero)) continue;
				if (add_to_fr(r)) return;
			}
		}

		BigWeight<6> delta = { (1LL << 60) - 1,(1LL << 60) - 1,(1LL << 60) - 1,(1LL << 60) - 1,(1LL << 60) - 1,(1LL << 60) - 1 };
		for (long long r = 0; r < n; ++r)
			if (!fr[r]) delta = min(delta, slack[r].first);

		if (delta == WeightINF) return;

		for (long long l = 0; l < n; ++l)
			if (fl[l]) lh[l] -= delta;

		for (long long r = 0; r < n; ++r) {
			if (fr[r]) rh[r] += delta;
			else slack[r].first -= delta;
		}

		for (long long r = 0; r < n; ++r) {
			if (fr[r] || !(slack[r].first == WeightZero)) continue;
			if (add_to_fr(r)) return;
		}
	}
}

BigWeight<6> hungarian(vector<vector<BigWeight<6>>>& weight,
	vector<long long>& lmatch, vector<long long>& rmatch,
	vector<BigWeight<6>>& lh, vector<BigWeight<6>>& rh)
{
	long long n = weight.size();

	for (long long l = 0; l < n; l++)
		lh[l] = *max_element(weight[l].begin(), weight[l].end());

	for (long long i = 0; i < n; i++)
		augment(weight, lmatch, rmatch, lh, rh);

	BigWeight<6> result = { 0,0,0,0,0,0 };
	for (long long l = 0; l < n; l++)
		result += weight[l][lmatch[l]];
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n; cin >> n;

	vector<vector<BigWeight<6>>> weight(n, vector<BigWeight<6>>(n, WeightZero));
	vector<long long> lmatch(n, -1), rmatch(n, -1);
	vector<vector<char>> data(n, vector<char>(n));
	for (int i = 0; i < n; ++i)
	{
		string input;
		cin >> input;

		for (int j = 0; j < n; ++j)
		{
			char ch = input[j];
			data[i][j] = ch;
			int num;
			if (ch >= 'a' && ch <= 'z')
				num = ch - 'a' + 26;
			else
				num = ch - 'A';

			num = 51 - num;
			// 64^52

			weight[i][j] = { 0,0,0,0,0,0 };
			weight[i][j].data[5 - (num / 10)] = (1LL << (6 * (num % 10)));
		}
	}

	vector<BigWeight<6>> lh(n, { 0,0,0,0,0,0 }), rh(n, { 0,0,0,0,0,0 });
	hungarian(weight, lmatch, rmatch, lh, rh);

	vector<char> result;

	for (int i = 0; i < n; ++i)
	{
		long long r = lmatch[i];
		result.push_back(data[i][r]);
	}

	sort(result.begin(), result.end());

	for (const auto& ch : result)
	{
		cout << ch;
	}
	cout << '\n';

	return 0;
}