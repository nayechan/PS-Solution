#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, s;
    cin >> n >> s;
    vector<int> data;
    data.reserve(n);

    for(int i=0;i<n;++i)
    {
        int input;
        cin >> input;
        data.push_back(input);
    }

    int left=0, right=0;
    int sum=0, min=0;

    while(left < n)
    {
        while(sum < s && right<n)
        {
            sum += data[right];
            ++right;
        }

        if(sum >= s && (min == 0 || min > right - left))
            min = right - left;

        sum -= data[left];
        ++left;
    }

    cout << min;

    return 0;
}