#include <iostream>
#include <climits>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    string str;
    cin >> str;

    int aCount = 0;
    int n = str.size();
    for(char ch : str)
    {
        if(ch == 'a')
            ++aCount;
    }
    
    int result = 0;
    for(int i=0;i<aCount;++i)
    {
        if(str[i] == 'b')
            ++result;
    }

    int count = result;
    for(int i=0;i<n;++i)
    {
        if(str[i] == 'b')
            --count;
        if(str[(i+aCount)%n] == 'b')
            ++count;
            
            
        result = min(result, count);
    }
    cout << result << endl;
    return 0;
}