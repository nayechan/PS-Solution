#include <iostream>
#include <vector>

using namespace std;

int main(){
	long long n;
	while (true)
	{
		cin >> n;
		if (!n) break;

		vector<long long> data(n+2);
		data[0] = 0;
		data[n + 1] = 0;
		for (long long i = 1; i <= n; ++i)
		{
			cin >> data[i];
		}

		vector<long long> stack;
		long long result = 0;
		stack.push_back(0);
		for (long long i = 1; i <= n+1; ++i)
		{
			while (stack.size() > 0 && data[stack.back()] > data[i])
			{
				long long lastIndex = stack.back();
				stack.pop_back();

				result = max(result, (i - stack.back() - 1) * data[lastIndex]);
			}
			stack.push_back(i);
		}

		cout << result << '\n';
	}
	
	return 0;
}