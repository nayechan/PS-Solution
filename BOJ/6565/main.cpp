#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    string str;
    do
    {
        cin >> str;
        auto plusPos = str.find('+');
        auto equalPos = str.find('=');

        string aStr(str.begin(), str.begin() + plusPos);
        string bStr(str.begin() + plusPos + 1, str.begin() + equalPos);
        string cStr(str.begin() + equalPos + 1, str.end());
        
        reverse(aStr.begin(), aStr.end());
        reverse(bStr.begin(), bStr.end());
        reverse(cStr.begin(), cStr.end());

        if(atoi(aStr.c_str()) + atoi(bStr.c_str()) == atoi(cStr.c_str()))
            cout << "True" << endl;
        else
            cout << "False" << endl;

    } while (str != "0+0=0");
    
    return 0;
}