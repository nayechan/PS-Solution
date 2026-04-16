#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

bool isCycle(vector<int> &cycleCache, vector<vector<int>> &vertices, unordered_set<int> &history, int index)
{
	if(cycleCache[index] != -1)
	{
		return cycleCache[index] == 1;
	}

	if(history.find(index) != history.end())
	{
		cycleCache[index] = true;
		return true;
	}

	history.insert(index);

	for(int next : vertices[index])
	{
		bool result = isCycle(cycleCache, vertices, history, next);
		if(result) 
		{
			cycleCache[index] = true;
			return true;
		}
	}

	history.erase(index);

	cycleCache[index] = false;
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n,m;
	cin >> n >> m;

	vector<vector<int>> vertices(n+1);
	vector<int> inEdgeCount(n+1, 0);
	vector<int> cycleCache(n+1, -1);
	unordered_set<int> history;

	for(int i=0;i<m;++i)
	{
		int u, v;
		cin >> u >> v;

		vertices[u].push_back(v);
		++inEdgeCount[v];
	}

	int count = 0;

	for(int i=1;i<=n;++i)
	{
		if(!isCycle(cycleCache, vertices, history, i))
			++count;
	}

	cout << count << endl;

	return 0;
}