#include <iostream>

using namespace std;

int main()
{
    int a, b, c ;
    cin >> a >> b >> c;

    int sum = a * 2;

    if (c >= 2)
    {
        sum += (b * 2);
        sum += ((c / 2) * 3);
    }

    cout << sum << endl;

    return 0;
}