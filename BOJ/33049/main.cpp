#include <iostream>
#include <cmath>

using namespace std;

pair<int,int> egcd(int a, int b)
{
    if(b==0)
        return {1,0};
    
    pair<int,int> result = egcd(b, a%b);
    return {result.second, result.first - (a/b) * result.second};
}

int gcd(int x, int y)
{
    return y!=0 ? gcd(y, x%y) : x;
}

int main()
{
    int a,b,c;
    cin >> a >> b >> c;
    
    int t1, t2;
    
    t1 = (int)ceil(a / 3.0);
    c -= (t1*3-a);
    
    t2 = (int)ceil(b / 4.0);
    c -= (t2*4-b);
    
    if(c>=0)
    {
        pair<int,int> _egcd = egcd(3,4);
        _egcd.first *= c;
        _egcd.second *= c;

        //3(x+t1+4t)+4(y+t2-3t) = a+b+c
        // x+4t >= 0, y-3t >= 0
        // t >= -x/4, t <= y/3
        // -x/4 <= t <= y/3

        int t3 = ceil(-_egcd.first/4.0);

        if(t3*3 > _egcd.second)
        {
            cout << "-1" << endl;
        }
        else
        {
            cout << t1+_egcd.first+t3*4 << " " << t2+_egcd.second-t3*3 << endl;
        }
    }
    else
    {
        cout << "-1" << endl;
    }
    
    return 0;
}
