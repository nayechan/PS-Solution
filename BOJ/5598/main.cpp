#include <iostream>

using namespace std;

int main()
{
    string str;
    cin >> str;

    for(char ch : str)
    {
        int diff = ch - 'A';
        diff += 23;
        
        diff %= 26;
        cout << (char)('A'+diff);
    }
    cout << endl;
    return 0;
}