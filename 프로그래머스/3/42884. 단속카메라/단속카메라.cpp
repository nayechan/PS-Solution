#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> routes) {
    
    sort(routes.begin(), routes.end(), [](const vector<int>& a, const vector<int>& b){
        return a[1] < b[1];
    });
    
    int lastCamera = -99999;
    int cameraCount = 0;
    
    for (const auto& t : routes)
    {
        if(t[0] > lastCamera)
        {
            ++cameraCount;
            lastCamera = t[1];
        }
    }
    
    
    int answer = cameraCount;
    return answer;
}