#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> routes) {
    
    vector<int> indice(60001, -1);
    
    for(const auto& route : routes)
    {
        indice[route[1]+30000] = max(indice[route[1]+30000],route[0]+30000);
    }
    
    int lastCamera = -1;
    int cameraCount = 0;
    for (int i=0;i<=60000;++i)
    {
        if(indice[i] == -1) continue;
        
        if(indice[i] > lastCamera)
        {
            ++cameraCount;
            lastCamera = i;
        }
    }
    
    
    int answer = cameraCount;
    return answer;
}