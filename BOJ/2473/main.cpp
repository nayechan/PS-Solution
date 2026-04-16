#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

int bisect(vector<int> & data, int s, int e, int query)
{
    if(s > e)
    {
        if(s>=data.size())
        {
            return e;
        }
        if(e<0)
        {
            return s;
        }
        if(abs(data[s] - query) < abs(data[e]-query))
        {
            return s;
        }
        else
        {
            return e;
        }
    }

    int targetIndex = (s+e)/2;
    int queryResult = data[targetIndex];

    if(queryResult == query)
        return targetIndex;

    else if (query < queryResult)
    {
        return bisect(data, s, targetIndex-1, query);
    }
    else
    {
        return bisect(data, targetIndex+1, e, query);
    }
}

int main()
{
    int n;
    cin >> n;

    int a = INT_MAX/2;
    int b = INT_MAX/2;

    vector<int> arr;
    arr.reserve(n);

    for(int i=0;i<n;++i)
    {
        int input;
        cin >> input;
        arr.push_back(input);
    }

    sort(arr.begin(), arr.end());

    for(int i=0;i<n;++i)
    {
        int queryResult = bisect(arr, 0, arr.size()-1, -arr[i]);
        for(int delta=-1;delta<=1;++delta)
        {
            int targetIndex = queryResult+delta;
            if(targetIndex < 0 || targetIndex >= arr.size()) continue;
            if(i != targetIndex)
            {
                int localA = arr[queryResult+delta];
                int localB = arr[i];

                if(localA > localB)
                    swap(localA, localB);

                if(abs(localA + localB) < abs(a + b))
                {
                    a = localA;
                    b = localB;
                }
            }
        }
    }

    cout << a << " " << b << endl;

    return 0;
}