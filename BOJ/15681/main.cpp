#include <iostream>
#include <vector>
#include <list>
#include <set>

using namespace std;

int getElementCount(vector<vector<int>> & nodes, vector<int> & dp, vector<bool> & visited, int index)
{
    if(dp[index] != -1) return dp[index];

    int sum = 1;

    visited[index] = true;
    for(auto node : nodes[index])
    {
        if(visited[node]) continue;
        sum += getElementCount(nodes, dp, visited, node);
    }

    dp[index] = sum;
    return sum;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, r, q;

    cin >> n >> r >> q;

    vector<vector<int>> nodes(n+1);

    for(int i=0;i<n-1;++i)
    {
        int a, b;
        
        cin >> a >> b;
        //a = 1;
        //b = i+2;

        nodes[a].push_back(b);
        nodes[b].push_back(a);
    }

    vector<int> dp(n+1, -1);
    vector<bool> visited(n+1, false);

    getElementCount(nodes, dp, visited, r);

    for(int i=0; i<q; ++i)
    {
        int _q;
        cin >> _q;

        cout << dp[_q] << '\n';
    }

    return 0;
}