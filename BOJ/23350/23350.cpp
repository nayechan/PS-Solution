#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define LIMIT (100+1)

void decreasePriority(int& currentPriority, const vector<int>& count)
{
	while (currentPriority > 0 && count[currentPriority] == 0)
		--currentPriority;
}

int main() {
	int m, n;
	cin >> n >> m;

	int currentPriority = LIMIT - 1;
	int cost = 0;

	vector<int> count(LIMIT, 0);
	queue<pair<int, int>> containerQueue; // first : priority, second : weight

	for (int i = 0; i < n; ++i)
	{
		int p, w;
		cin >> p >> w;

		--p;

		containerQueue.push({ p,w });

		++count[p];
	}

	priority_queue<pair<int, int>> tempStack;
	stack<pair<int, int>> _stack;

	decreasePriority(currentPriority, count);

	while (!containerQueue.empty())
	{
		pair<int, int> current = containerQueue.front();
		containerQueue.pop();
		if (current.first != currentPriority)
		{
			containerQueue.push(current);
			cost += current.second;
			continue;
		}

		--count[currentPriority];

		while (!_stack.empty() && _stack.top().second < current.second)
		{
			pair<int, int> top = _stack.top();
			tempStack.push(top);
			cost += top.second;
			_stack.pop();
		}

		_stack.push(current);
		cost += current.second;

		while (!tempStack.empty())
		{
			pair<int, int> top = tempStack.top();
			_stack.push(top);
			cost += top.second;
			tempStack.pop();
		}

		if (count[currentPriority] == 0)
		{
			while (!_stack.empty())
				_stack.pop();
			decreasePriority(currentPriority, count);
		}
	}

	cout << cost << endl;


	return 0;
}