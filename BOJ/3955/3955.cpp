#include <iostream>
#include <cmath>

using namespace std;

long long gcd(long long a, long long b)
{
    return b ? gcd(b, a%b) : a;
}

//get pair of {x,y} where ax+by=gcd(a,b)
pair<long long, long long> egcd(long long a, long long b)
{
    pair<long long, long long> result = {0,0};

    if(b == 0)
    {
        return {1,0};
    }

    pair<long long, long long> prev = egcd(b, a%b);
    return {prev.second, prev.first - (a/b) * prev.second};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

	long long n;
	cin >> n;
	for(int i=0;i<n;++i)
	{
		//-KX+CY = 1 exists?
		long long k,c;
		cin >> k >> c;

		// check if 1 % gcd(k,c) == 0 (gcd(k,c) == 1)
		if(gcd(k,c)==1)
		{
			// k*(-x)+cy = 1
			pair<long long,long long> result = egcd(k, c);
			result.first *= -1; // convert -x to x

			// (x+t*c) >= 1, ct >= 1-x t >= 1-x/c
			long long t = ceil((double)(1-result.first) / (double)c);
			result.first += t*c;

			long long totalCandy = k*result.first+1;
			result.second = totalCandy / c;

			if(result.second <= 1000000000)
				cout << totalCandy / c << '\n';
			
			else
				cout << "IMPOSSIBLE\n";
		}
		else
		{
			cout << "IMPOSSIBLE\n";
		}
	}

    return 0;
}