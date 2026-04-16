#include <iostream>

using namespace std;

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    
    int n;
    cin >> n;

    string str;
    cin >> str;

    string total = "";
    long long sum = 0;
    for(const auto & ch : str)
    {
        if ('0' <= ch && ch <= '9')
        {
            total += ch;

            if(total.size() >= 6)
            {
                sum += atoi(total.c_str());
                total = "";
            }
        }
        else
        {
            if(total.size() > 0)
            {
                sum += atoi(total.c_str());
                total = "";
            }
        }
    }
    sum += atoi(total.c_str());
    cout << sum << endl;
    return 0;
}