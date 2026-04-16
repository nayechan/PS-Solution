#include <iostream>
#include <set>
#include <cmath>
#include <ctime>

using namespace std;

string get_random_string(char s, char e, int m)
{
    string str = "";
    for (int i = 0;i < m;++i)
    {
        char ch = s + (rand() % (e - s + 1));
        str += ch;
    }

    return str;
}

string fast_solution(set<string>& strings, char s, char e, int m)
{
    string result = get_random_string(s, e, m);
    while (strings.find(result) != strings.end())
    {
        result = get_random_string(s, e, m);
    }
    return result;
}

string solution(set<string>& strings, string prefix, char s, char e, int m)
{
    if (pow(s - e + 1, m) > 20000.0f)
    {
        return fast_solution(strings, s, e, m);
    }


    if (m == 0)
    {
        if (strings.find(prefix) != strings.end())
            return "";

        return prefix;
    }

    for (char q = s; q <= e; ++q)
    {
        string result = solution(strings, prefix + q, s, e, m - 1);
        if (result != "") return result;
    }

    return "";
}

int main()
{
    srand(time(NULL));
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    for (int _t = 0;_t < t;++_t)
    {
        int n, m, k;
        cin >> n >> m >> k;
        string str;
        cin >> str;

        set<string> strings;
        for (int i = 0;i < n-m+1;++i)
        {
            string substr = str.substr(i, m);
            strings.insert(substr);
        }

        char s = 'a';
        char e = s + k - 1;
        string result = solution(strings, "", s, e, m);
        cout << result << endl;
    }
    return 0;
}