#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

struct edge {
	int from;
	int to;
	int cost;
	bool visited = false;

	int dest(int inFrom)
	{
		if (from == inFrom)
			return to;

		if (to == inFrom)
			return from;

		return -1;
	}
};

int find(vector<int>& root, int a)
{
	while (root[a] != a)
	{
		a = root[a];
	}

	return a;
}

void connect(vector<int>& root, vector<int>& rank, int a, int b)
{
	int rootA = find(root, a);
	int rootB = find(root, b);
	if (rootA == rootB) return;

	if (rank[rootA] < rank[rootB])
	{
		root[rootA] = rootB;
	}
	else
	{
		root[rootB] = rootA;
		if (rank[rootA] == rank[rootB])
		{
			++rank[rootA];
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;

	int connectedCount = 0;
	int paidConnectedCount = 0;
	vector<edge*> resultEdges;
	vector<int> root(n + 1);
	vector<int> rank(n + 1, 0);
	iota(root.begin(), root.end(), 0);

	auto comp = [](edge* a, edge* b) {
		return a->cost > b->cost;
	};
	priority_queue<edge*, vector<edge*>, decltype(comp)> pq(comp);

	for (int i = 0;i < m;++i)
	{
		int a, b;
		cin >> a >> b;
		if (n <= 2 || (a != 1 && b != 1))
		{
			edge* e = new edge{ min(a,b),max(a,b), 0 };
			pq.push(e);
		}
	}

	for (int i = 1;i <= n;++i)
	{
		for (int j = 1;j <= n;++j)
		{
			int c;
			cin >> c;
			if ((n<=2 || (i!=1 && j!=1)) && i < j)
			{
				edge* e = new edge{ min(i,j),max(i,j), c };
				pq.push(e);
			}
		}
	}

	int cost = 0;
	while (connectedCount < n-1 && !pq.empty())
	{
		edge* e = pq.top();
		if (find(root, e->from) == find(root, e->to))
		{
			pq.pop();
			continue;
		}

		//cout << e->from << "/" << e->to << "/" << e->cost << endl;
		connect(root, rank, e->from, e->to);
		resultEdges.push_back(e);
		pq.pop();
		++connectedCount;
		if (e->cost > 0) ++paidConnectedCount;
		cost += e->cost;
	}

	
	cout << cost << " " << paidConnectedCount << endl;

	for (edge* e : resultEdges)
	{
		if (e->cost <= 0) continue;
		cout << e->from << " " << e->to << endl;
	}

	return 0;
}