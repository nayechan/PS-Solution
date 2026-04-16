#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<int> fareCount(1001);

	int jinju = -1;
	int count = 0;

	for(int i=0;i<n;++i)
	{
		string input;
		cin >> input;

		long long fare;
		cin >> fare;

		if(input == "jinju")
			jinju = fare;
		
		else if(fare > 1000)
			++count;
		
		else
			++fareCount[(int)fare];
	}

	for(int i=jinju+1;i<=1000;++i)
	{
		count += fareCount[i];
	}

	cout << jinju << endl << count << endl;

	return 0;
}