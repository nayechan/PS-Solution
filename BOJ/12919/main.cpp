#include <iostream>
#include <algorithm>

using namespace std;

bool checkStr(string & t, const string & s)
{
    if (t == s) return true;

    if (t.size() <= s.size()) return false;

    bool success = false;

    if (t.back() == 'A')
    {
        t.pop_back();
        success = success || checkStr(t, s);
        t.push_back('A');
    }

    if (t.front() == 'B')
    {
        reverse(t.begin(), t.end());
        t.pop_back();
        success = success || checkStr(t, s);
        t.push_back('B');
        reverse(t.begin(), t.end());
    }

    return success;
}

int main()
{
    string s, t;
    cin >> s >> t;

    bool success = checkStr(t, s);

    cout << ((success) ? 1 : 0);
    return 0;
}