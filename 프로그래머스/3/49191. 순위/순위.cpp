#include <string>
#include <vector>
#include <bitset>

using namespace std;

int solution(int n, vector<vector<int>> results) {
    
    vector<bitset<100>> dist(n), invDist(n);
    
    for(int i=0;i<n;++i)
    {
        dist[i][i] = 1;
        invDist[i][i] = 1;
    }
    
    for(const auto &v : results)
    {
        int from = v[0]-1;
        int to = v[1]-1;
        dist[from][to] = 1;
        invDist[to][from] = 1;
    }
    
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(dist[j][i])
                dist[j] |= dist[i];
        }
    }
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(invDist[j][i])
                invDist[j] |= invDist[i];
        }
    }
    int answer = 0;
    for(int i=0;i<n;++i)
    {
        if(dist[i].count() + invDist[i].count() == n+1)
            ++answer;
    }
    return answer;
}