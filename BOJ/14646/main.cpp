#include <iostream>
#include <stack>
#include <set>

using namespace std;

int main()
{
    int n;
    cin >> n;

    stack<int> data;

    for(int i=0;i<2*n;++i)
    {
        int input;
        cin >> input;
        data.push(input);
    }

    int max = 0;
    set<int> stickers;

    while(!data.empty())
    {
        int element = data.top(); data.pop();
        if(stickers.find(element) == stickers.end())
        {
            stickers.insert(element);
            if(max < stickers.size())
                max = stickers.size();
        }
        else
        {
            stickers.erase(element);
        }
    }

    cout << max << endl;

    return 0;
}