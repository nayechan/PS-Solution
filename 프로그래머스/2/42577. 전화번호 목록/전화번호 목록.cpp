#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

bool solution(vector<string> phone_book) {
    bool answer = true;
    unordered_set<string> check;
    for(const auto& str : phone_book)
    {
        check.insert(str);
    }
    for(const auto& str : phone_book)
    {
        string current = "";
        int count = 0;
        for(const auto& ch : str)
        {
            current += ch;
            if(check.find(current) != check.end())
            {
                //cout << current << endl;
                ++count;
            }
            
            if(count >= 2)
            {
                answer = false;
                break;
            }
        }
        if(!answer)
            break;
    }
    return answer;
}