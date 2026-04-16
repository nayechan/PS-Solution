#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;

    unordered_set<int> data;
    for(int i=0;i<n;++i)
    {
        int input;
        cin >> input;
        data.insert(input);
    }

    int targetSum;
    cin >> targetSum;

    int count = 0;
    for(int e : data)
    {
        if(targetSum - e != e && data.find(targetSum - e) != data.end())
            ++count;
    }

    cout << count/2 << endl;
    return 0;
}