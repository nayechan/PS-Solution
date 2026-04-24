#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> scores) {
    int n = scores.size();
    vector<int> data(100002, -1);
    for(auto& score : scores)
    {
        data[score[0]] = max(data[score[0]], score[1]);
    }
    for (int i=data.size()-2;i>=0;--i)
    {
        data[i] = max(data[i+1], data[i]);
    }
    
    vector<pair<int,int>> total(n);
    
    for(int i=0;i<n;++i)
    {
        auto& score = scores[i];
        if(data[score[0]+1] <= score[1])
        {
            total[i] = {score[0]+score[1], i};
        }
        else
        {
            total[i] = {-1, i};
        }
    }
    
    bool isValid = (total[0].first != -1);
    
    sort(total.begin(), total.end(), greater<pair<int,int>>());
    
    vector<int> rank(n);
    
    rank[total[0].second] = 1;
    for(int i=1;i<n;++i)
    {
        if(total[i-1].first > total[i].first)
            rank[total[i].second] = (i+1);
        else
            rank[total[i].second] = rank[total[i-1].second];
    }
    
    int answer = rank[0];
    if(!isValid) answer = -1;
    return answer;
}