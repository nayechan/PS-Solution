#include <iostream>

using namespace std;

int main()
{
    string str;
    cin >> str;

    bool containsUnderBar = false, containsUpperCase = false;
    bool underBarError = false;
    bool wasUnderBar = false;

    for(const auto & ch : str)
    {
        if(ch == '_')
        {
            if(wasUnderBar)
            {
                underBarError = true;
                break;
            }
            
            wasUnderBar = true;
            containsUnderBar = true;
        }
        else
        {
            wasUnderBar = false;
        }
    }
    for(const auto & ch : str)
    {
        if(isupper(ch))
        {
            containsUpperCase = true;
            break;
        }
    }

    int index = 0;
    if(containsUnderBar && containsUpperCase || isupper(str[0]) || str[0] == '_' || str.back() == '_' || underBarError)
    {
        cout << "Error!";
    }
    else if(containsUnderBar)
    {
        bool prevUnderbar = false;
        for(char ch : str)
        {
            if(ch == '_')
            {
                prevUnderbar = true; 
                ++index;      
                continue;
            }

            if(prevUnderbar)
            {
                cout << (char)toupper(ch);
                prevUnderbar = false;
                continue;
            }

            cout << ch;     
        }
    }
    else
    {
        for(char ch : str)
        {
            if(isupper(ch))
                cout << '_' << (char)tolower(ch);
            else
                cout << ch;
        }
    }
    
    return 0;
}