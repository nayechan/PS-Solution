#include <string>
#include <queue>
#include <sstream>
#include <iostream>

using namespace std;

vector<int> solution(vector<string> operations) {
    priority_queue<int, vector<int>, greater<int>> minQ, deletedMin;
    priority_queue<int, vector<int>, less<int>> maxQ, deletedMax;
    
    for(string & op : operations)
    {
        stringstream ss(op);
        char _op;
        int v;
        ss >> _op >> v;
        if(_op == 'I')
        {
            minQ.push(v);
            maxQ.push(v);
        }
        else
        {
            if(v == 1)
            {
                if(maxQ.empty()) continue;
                int target = maxQ.top();
                maxQ.pop();
                deletedMin.push(target);
                //cout << target << "\n";
            }
            else
            {
                if(minQ.empty()) continue;
                int target = minQ.top();
                minQ.pop();
                deletedMax.push(target);
                //cout << target << "\n";
            }
            
            while(!minQ.empty() && !deletedMin.empty() && minQ.top() == deletedMin.top())
            {
                minQ.pop();
                deletedMin.pop();
            }
            
            while(!maxQ.empty() && !deletedMax.empty() && maxQ.top() == deletedMax.top())
            {
                maxQ.pop();
                deletedMax.pop();
            }
        }
    }
    vector<int> answer(2, 0);
    answer[0] = maxQ.empty() ? 0 : maxQ.top();
    answer[1] = minQ.empty() ? 0 : minQ.top();
    return answer;
}