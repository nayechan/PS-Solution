#include <string>
#include <vector>

using namespace std;
void dfs(int v,
         const vector<vector<int>>& child, const vector<int>& a,
         vector<int>& in, vector<int>& out, vector<long long>& sum,
         int& timer, int parent = -1)
{
    sum[timer] = a[v];
    if(timer > 0)
        sum[timer] += sum[timer - 1];
    in[v] = timer++;
    for (int u : child[v])
        if(u != parent)
            dfs(u, child, a, in, out, sum, timer, v);
    out[v] = timer - 1;
}

long long solution(vector<int> a, vector<vector<int>> edges) {
    int n = a.size();
    
    vector<int> in(n+1, -1), out(n+1, -1);
    vector<long long> sum(n+1, 0);
    
    vector<vector<int>> tree(n);
    for(const auto& edge : edges)
    {
        tree[edge[0]].push_back(edge[1]);
        tree[edge[1]].push_back(edge[0]);
    }
    
    int v = -1;
    for(int i=0;i<n;++i)
    {
        if(tree[i].size() == 1)
        {
            v = i;
            break;
        }
    }
    
    int timer = 0;
    dfs(v, tree, a, in, out, sum, timer);
    
    if(sum[n-1] != 0) return -1;
    
    long long answer = 0;
    
    for(int i=0;i<n;++i)
    {
        if(i == v) continue;
        long long subtreeSum = 0;
        subtreeSum += sum[out[i]];
        if(in[i]-1 >= 0)
            subtreeSum -= sum[in[i]-1];
        
        answer += abs(subtreeSum);
    }
    
    return answer;
}