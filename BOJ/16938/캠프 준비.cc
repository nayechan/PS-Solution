#include <iostream>
#include <vector>
#include <climits>

using namespace std;

bool validate(vector<long long>& a, long long l, long long r, long long x, long long bit)
{
	long long sum = 0;
	long long _min = LLONG_MAX, _max = LLONG_MIN;
	for (long long i = 0; i < a.size(); i++) {
		if (bit & (1LL << i)) {
			sum += a[i];
			_min = min(_min, a[i]);
			_max = max(_max, a[i]);
		}
	}
	return l <= sum && sum <= r && _max - _min >= x;
}

int main()
{
	long long n, l, r, x;
	cin >> n >> l >> r >> x;

	vector<long long> a(n);
	for (long long i = 0; i < n; i++) {
		cin >> a[i];
	}

	long long count = 0;
	for (long long bit = 0; bit < (1LL << n); ++bit)
	{
		if (validate(a, l, r, x, bit)) ++count;
	}

	cout << count << endl;
}