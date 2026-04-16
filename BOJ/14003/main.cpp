#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> data(n), index(n), cache;

    cin >> data[0];
    cache.push_back(data[0]);

    for(int i=1;i<n;++i)
    {
        int _index = -1;
        cin >> data[i];
        if(cache.back() < data[i])
        {
            cache.push_back(data[i]);
            _index = cache.size() - 1;
        }
        else
        {
            auto itr = lower_bound(cache.begin(), cache.end(), data[i]);
            if(*itr > data[i])
            {
                *itr = data[i];
                _index = itr - cache.begin();
            }
        }
        
        index[i] = _index;
    }

    stack<int> result;
    cout << cache.size() << endl;
    for(int i=index.size()-1, target=cache.size()-1; i>=0 && target>=0; --i)
    {
        if(index[i] == target)
        {
            result.push(data[i]);
            --target;
        }
    }
    
    while(!result.empty())
    {
        cout << result.top() << " ";
        result.pop();
    }
}