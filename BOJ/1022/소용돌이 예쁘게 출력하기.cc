#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int getNum(int r, int c)
{
	int radius = max(abs(r),abs(c));

	int result = (2*radius+1);
	result *= result;

	if(r==radius)
	{
		result += (c-radius);
	}
	else if(r==-radius)
	{
		result += (-c-5*radius);
	}
	else if(c==-radius)
	{
		result += (r-3*radius);
	}
	else if(c==radius)
	{
		result += (-r-7*radius);
	}

	return result;
}

int main() {
	// 코드 작성
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int r1, c1, r2, c2;
	cin >> r1 >> c1 >> r2 >> c2;

	int max = 0;
	for(int i=r1;i<=r2;++i)
	{
		for(int j=c1;j<=c2;++j)
		{
			int result = getNum(i,j);
			if(result > max) max = result;
		}
	}

	int maxDigitCount = to_string(max).size();
	
	for(int i=r1;i<=r2;++i)
	{
		for(int j=c1;j<=c2;++j)
		{
			int result = getNum(i,j);

			int digitCount = to_string(result).size();
			if(j != c1)
			{
				for(int k=0;k<=maxDigitCount-digitCount;++k)
				{
					cout << " ";
				}
			}
			else
			{
				for(int k=0;k<maxDigitCount-digitCount;++k)
				{
					cout << " ";
				}
			}
			cout << result;
		}
		cout << '\n';
	}
	return 0;
}