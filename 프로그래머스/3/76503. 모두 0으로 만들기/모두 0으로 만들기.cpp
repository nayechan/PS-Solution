#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

long long solution(vector<int> a, vector<vector<int>> edges) {
    long long answer = 0;
    
    vector<long long> _a(a.begin(), a.end());
    
    int n = a.size();
    vector<int> inEdge(n, 0);
    vector<vector<int>> tree(n);
    for(const auto& edge : edges)
    {
        tree[edge[0]].push_back(edge[1]);
        tree[edge[1]].push_back(edge[0]);
        
        ++inEdge[edge[0]];
        ++inEdge[edge[1]];
    }
    
    queue<int> q;
    for(int i=0;i<n;++i)
    {
        if(inEdge[i] == 1)
        {
            q.push(i);
        }
    }
    
    int current = -1;
    while(!q.empty())
    {
        current = q.front();
        //cout << current << endl;
        q.pop();
        inEdge[current] = 0;
        for(const auto& e : tree[current])
        {            
            if(inEdge[e] == 0) continue;
            inEdge[e]--;
            _a[e] += _a[current];
            answer += abs(_a[current]);
            //cout << current << " -> " << e << " : " << abs(a[current]) << endl;
            _a[current] = 0;
            if(inEdge[e] == 1)
                q.push(e);
        }
            
    }
    
    if(_a[current] != 0)
        answer = -1;
    
    
    return answer;
}