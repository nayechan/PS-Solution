#include <iostream>
#include <array>
#include <string>

using namespace std;

array<long long, 10> sum(const array<long long, 10>& a, const array<long long, 10>& b)
{
    array<long long, 10> result = { 0,0,0,0,0,0,0,0,0,0 };
    for (int i = 0;i < 10;++i)
    {
        result[i] = a[i] + b[i];
    }
    return result;
}

array<long long, 10> sub_sol(long long a, long long b, long long rate = 1)
{
    array<long long, 10> result = { 0,0,0,0,0,0,0,0,0,0 };

    while (true)
    {
        if (b - a < 10)
        {
            for (long long i = a;i <= b;++i)
            {
                string str = to_string(i);
                for (char c : str)
                {
                    int v = c - '0';
                    result[v] += rate;
                }
            }
            return result;
        }

        if (b % 10 != 9)
        {
            //return sum(sub_sol(a, b - (b % 10) - 1), sub_sol(b - (b % 10), b));
            for (long long i = b - (b % 10);i <= b;++i)
            {
                string str = to_string(i);
                for (char c : str)
                {
                    int v = c - '0';
                    result[v] += rate;
                }
            }
            b = b - (b % 10) - 1;
        }

        long long count = b / 10 - a / 10 + 1;
        for (int i = 0;i < 10;++i)
        {
            result[i] += count * rate;
        }

        rate *= 10;
        a /= 10;
        b /= 10;
    }

    
    return result;
}

array<long long, 10> sol(long long n)
{
    array<long long, 10> result = { 0,0,0,0,0,0,0,0,0,0 };

    if (n < 10)
    {
        for (int i = 1;i <= n;++i)
        {
            ++result[i];
        }
        return result;
    }

    int num = 1;
    while (num * 10 <= n)
    {
        num *= 10;
    }
    return sum(sol(num - 1), sub_sol(num, n));
}

int main()
{
    long long n;
    cin >> n;

    array<long long, 10> result = sol(n);
    for (int i = 0; i < 10; ++i)
    {
        cout << result[i] << " ";
    }

    return 0;
}