#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cout.tie(0);
	cin.tie(0);

    int t;
    cin >> t;

    for(int _t = 0; _t < t; ++_t)
    {
        int n, left_remove = 0, right_remove = 0;
        string operation;
        string input;

        cin >> operation >> n >> input;

        vector<int> data;

        data.reserve(n);

        input = input.substr(1, input.size()-2);

        string token = "";
        stringstream tokenizer(input);

        while(getline(tokenizer, token, ','))
        {
            data.push_back(stoi(token));
        }

        bool isReversed = false;

        for(auto op : operation)
        {
            if(op == 'R')
            {
                isReversed = !isReversed;
            }
            if(op == 'D')
            {
                if(!isReversed)
                {
                    ++left_remove;
                }
                else
                {
                    ++right_remove;
                }
            }
        }

        if(left_remove + right_remove > data.size())
        {
            cout << "error" << endl;
        }
        else
        {
            cout << "[";
            if(isReversed)
            {
                for(auto itr = data.rbegin() + right_remove; itr != data.rend() - left_remove; ++itr)
                {
                    cout << *itr;
                    if(itr != data.rend() - left_remove - 1)
                        cout << ",";
                }
            }
            else
            {
                for(auto itr = data.begin() + left_remove; itr != data.end() - right_remove; ++itr)
                {
                    cout << *itr;
                    if(itr != data.end() - right_remove - 1)
                        cout << ",";
                }
            }
            cout << "]" << endl;
        }
    }

    return 0;
}
