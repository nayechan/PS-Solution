#include <string>
#include <vector>
#include <climits>
#include <iostream>

using namespace std;

bool check(int a, int b, vector<int> &g, vector<int> &s, vector<int> &w, vector<int> &t, long long d)
{
    long long n = g.size();
    
    long long _a = 0;
    long long _b = 0;
    long long cap = 0;
    
    for(int i=0;i<n;++i)
    {
        long long rep = (d + t[i]) / (2 * t[i]);
        
        _a += min(rep*w[i], (long long)g[i]);
        _b += min(rep*w[i], (long long)s[i]);
        cap += min(rep*w[i], (long long)(g[i]+s[i]));
    }
    
    //cout << d << " : " << _a << " " << _b << " " << cap << endl;
    if(a > _a || b > _b || a+b > cap) return false;
    return true;
}

long long solution(int a, int b, vector<int> g, vector<int> s, vector<int> w, vector<int> t) {
    long long l=0, r=1e16;
    
    while(l < r)
    {
        long long m = l + (r-l)/2;
        if(check(a,b,g,s,w,t,m))
        {
            r=m;
        }
        else
        {
            l=m+1;
        }
    }
    
    long long answer = r;
    return answer;
}