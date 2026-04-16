#include <iostream>
#include <cmath>

using namespace std;

int gcd(int a, int b)
{
    return b ? gcd(b, a%b) : a;
}

//get pair of {x,y} where ax+by=gcd(a,b)
pair<int,int> egcd(int a, int b)
{
    pair<int,int> result = {0,0};

    if(b == 0)
    {
        return {1,0};
    }

    pair<int,int> prev = egcd(b, a%b);
    return {prev.second, prev.first - (a/b) * prev.second};
}

int getMinute(string str)
{
    int h = atoi(str.substr(0,2).c_str());
    int m = atoi(str.substr(3,2).c_str());

    return h*60+m;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string startAStr, startBStr, delayAStr, delayBStr;
    cin >> startAStr >> startBStr >> delayAStr >> delayBStr;

    int a,b,c,d;
    string days[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    //ax+b = cy+d, ax-cy = d-b
    a = getMinute(delayAStr);
    b = getMinute(startAStr);

    c = getMinute(delayBStr);
    d = getMinute(startBStr);

    // ax-cy = d-b, check if gcd(a,c)|d-b
    int _gcd = gcd(a,c);
    if((d-b) % _gcd == 0)
    {
        pair<int,int> result = egcd(a,c);
        // TODO : Implement further calculation later
        result.first *= ((d-b) / _gcd);
        result.second *= (-(d-b) / _gcd);

        //ax0+b = cy0+d -> adjust x to be minimal positive
        //step shoulbe lcm/a / lcm/c
        // lcm/a = a*c/gcd(a,c)/a = c/gcd(a,c)

        int step = c/_gcd;
        //a(x0+step*t)+b >= (max(b,d)), so t >= -(ax0+b-max(b,d))/a*step
        int t = (int)ceil(-(double)(a*result.first+b-max(b,d))/(double)(a*step));

        int _result = a*(result.first+step*t)+b;
        int day = (_result/1440);

        cout << days[day%7] << '\n';

        cout.width(2);
        cout.fill('0');

        cout << (_result/60)%24 << ":";

        cout.width(2);
        cout.fill('0');

        cout << (_result%60) << '\n';

    }
    else
    {
        cout << "Never" << '\n';
    }

    return 0;
}