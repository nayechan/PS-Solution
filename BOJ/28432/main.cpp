#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    
    vector<string> data(n);

    for(int i=0;i<n;++i)
    {
        string input;
        cin >> input;

        data[i] = input;
    }

    auto itr = find(data.begin(), data.end(), "?");

    string _prev = "", _next = "";

    if(itr != data.begin())
    {
        _prev = *prev(itr);
    }

    if(next(itr) != data.end())
    {
        _next = *next(itr);
    }

    int m;
    cin >> m;

    char s = _prev.back(), e = _next.front();
    string result = "";

    for(int i=0;i<m;++i)
    {
        string input;
        cin >> input;

        if(
            (input.front() == s || _prev == "") && 
            (input.back() == e || _next == "") && 
            find(data.begin(), data.end(), input) == data.end())
        {
            result = input;
        }
    }
    cout << result << endl;
    return 0;
}