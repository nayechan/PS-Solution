#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

bitset<501> graph[501], invGraph[501];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		--a; --b;
		graph[a][b] = 1;
		invGraph[b][a] = 1;
	}

	for (int i = 0; i < n; i++) graph[i][i] = 1;
	for (int i = 0; i < n; i++) invGraph[i][i] = 1;

	for (int mid = 0; mid < n; mid++) {
		for (int s = 0; s < n; s++) {
			if (graph[s][mid]) {
				graph[s] |= graph[mid];
			}
			if (invGraph[s][mid]) {
				invGraph[s] |= invGraph[mid];
			}
		}
	}

	int count = 0;
	for (int i = 0; i < n; ++i)
	{
		if ((int)graph[i].count()+(int)invGraph[i].count() == n+1)
			++count;
	}

	cout << count << '\n';
	
	return 0;
}