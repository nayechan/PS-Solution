#include <iostream>
#include <string>
#include  <cmath>

using namespace std;

bool isImyun(int x)
{
	if(x < 7) return false;

	string strX = to_string(x);
	int sum = 0;
	bool status = false;

	for(char ch : strX)
	{
		sum += (ch%2);
	}

	return sum%2;
}

bool isImhyun(int x)
{
	if(x==2 || x==4) return true;

	int originalX = x;
	int count = 0;
	for(int i=2;i*i<=originalX;++i)
	{
		if(x%i==0)
		{
			++count;
			while(x%i==0)
			{
				x/=i;
			}
		}
	}

	if(x>1) ++count;

	return count!=0 && count%2==0;
}

int main() {
	int x;
	cin >> x;

	bool imyun = isImyun(x), imhyun = isImhyun(x);
	
	int result[4] = {3,1,2,4};
	cout << result[imyun | (imhyun << 1)] << endl;

	return 0;
}