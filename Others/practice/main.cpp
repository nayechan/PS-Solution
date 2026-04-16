#include <iostream>
#include <queue>

using namespace std;

int main()
{
	priority_queue<int> pq;
	int n;
	cin >> n;
	
	for(int i=0;i<n;++i)
	{
		int input;
		cin >> input;
		pq.push(input);
	}
	
	int max = pq.top();
	double sum = 0;

	while(!pq.empty())
	{
		int e = pq.top(); pq.pop();
		sum += ((double)e / (double)max * 100.0);
	}
	sum /= (double)n;
	cout << sum << endl;
	return 0;
}