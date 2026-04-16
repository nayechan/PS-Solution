#include <iostream>

using namespace std;

string makePoly(int count)
{
    string result = "";
    if (count % 2 != 0)
    {
        return "-1";
    }

    for(int i=0;i<count/4;++i)
        result += "AAAA";

    if(count%2 == 0)
        result += "BB";

    return result;
}

int main()
{
    string input;
    cin >> input;

    int count = 0;
    string result = "";

    for(char ch : input)
    {
        if(ch == '.')
        {
            string localResult = makePoly(count);
            if(localResult == "-1")
            {
                result = "-1";
                break;
            }
            result += localResult;
            result += ".";
            count = 0;
        }
        else
            ++count;
    }
    string localResult = makePoly(count);
    if(localResult == "-1")
    {
        result = "-1";
    }
    else
        result += localResult;
    cout << result << endl;
}