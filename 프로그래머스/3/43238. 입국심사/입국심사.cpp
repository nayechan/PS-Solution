#include <string>
#include <vector>
#include <iostream>

using namespace std;

long long count(vector<int>& times, long long d)
{
    long long result = 0;
    for(const auto& time : times)
    {
        result += (d/time);
    }
    
    return result;
}

long long solution(int n, vector<int> times) {
    long long answer = 0;
    long long l = 0, r = 1e18;
    
    while(l < r)
    {
        long long m = l + (r-l)/2;
        
        if(count(times, m) < n)
        {
            l = m+1;
        }
        else
        {
            r = m;
        }
    }
    
    answer = r;
    return answer;
}