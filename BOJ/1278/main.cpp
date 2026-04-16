#include <iostream>

using namespace std;

void solution(int n)
{
    if(n == 0) return;

    solution(n-1);
    cout << n << endl;
    solution(n-1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;

    cout << (1<<n)-1 << endl;

    solution(n);
    cout << n << endl;

    return 0;
}