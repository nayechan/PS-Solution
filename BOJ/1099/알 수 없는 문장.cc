#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cstring>

using namespace std;

int n;
string str;
int dp[51] = { 0, };
unordered_set<string> word;

bool isSame(const string& a, const string& b)
{
	unordered_map<char, int> chCount;
	for (const char& ch : a)
	{
		chCount[ch]++;
	}
	for (const char& ch : b)
	{
		chCount[ch]--;
	}

	for (const auto& p : chCount)
	{
		if (p.second != 0) return false;
	}

	return true;
}

int diffCount(const string& a, const string& b)
{
	int result = 0;
	int n2 = a.size();
	for (int i = 0; i < n2; ++i)
	{
		if (a[i] != b[i]) ++result;
	}

	return result;
}

int get(int idx)
{
	if (idx > str.size()) return -1;
	if (idx == str.size()) return 0;
	if (dp[idx] != -1) return dp[idx];

	int result = -1;

	for (const auto &w : word)
	{
		string sub = str.substr(idx, w.size());

		if (isSame(sub, w))
		{
			int localResult = get(idx + w.size());
			if (localResult <= -1) continue;
			
			localResult+=diffCount(sub, w);
			if (localResult > -1 && (result == -1 || localResult < result)) result = localResult;
		}
	}

	if (result == -1) --result;
	dp[idx] = result;

	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> str;
	cin >> n;

	for (int i = 0; i < n; ++i)
	{
		string input;
		cin >> input;
		word.insert(input);
	}

	memset(dp, -1, sizeof(dp));

	int result = get(0);

	if (result == -2) ++result;

	cout << result << '\n';

	return 0;
}