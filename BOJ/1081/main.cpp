#include <iostream>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

long long sumUntilN(long long n)
{
    return n * (n + 1) / 2;
}

constexpr int exp10(int n)
{
    constexpr int arr[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };

    if (n < 10)
        return arr[n];

    else return -1;
}

long long solution(int n)
{
    if (n < 10)
    {
        return sumUntilN(n);
    }

    string str = to_string(n);

    int len = str.size();
    int explen = exp10(len - 1);
    int prefixNumber = str[0] - '0';

    long long sum = 0;
    sum += prefixNumber * solution(explen - 1);
    sum += explen * sumUntilN(prefixNumber - 1);

    int remainder = stoi(str.substr(1));
    sum += prefixNumber * (remainder + 1);
    sum += solution(remainder);

    return sum;
}

int main()
{
    int l, u;
    cin >> l >> u;

    cout << solution(u) - solution(l-1) << endl;
    return 0;
}