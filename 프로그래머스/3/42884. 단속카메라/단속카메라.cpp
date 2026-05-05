#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

static unsigned short indice[60002];

int solution(vector<vector<int>> routes) {    
    for(const auto& route : routes)
    {
        if(indice[route[1]+30001] < route[0]+30001)
            indice[route[1]+30001] = route[0]+30001;
    }
    
    unsigned short lastCamera = 0;
    unsigned short cameraCount = 0;
    for (unsigned short i=1;i<=60001;++i)
    {
        if(indice[i] == 0) continue;
        
        if(indice[i] > lastCamera)
        {
            ++cameraCount;
            lastCamera = i;
        }
    }
    
    
    int answer = cameraCount;
    return answer;
}