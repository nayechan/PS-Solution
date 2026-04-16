#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<vector<int>> & map, int i, int j)
{
    int m = map.size();
    int n = map[0].size();

    vector<pair<int,int>> delta={{0,1},{0,-1},{1,0},{-1,0}};
    for(const auto & d : delta)
    {
        pair<int,int> target = {i+d.first, j+d.second};

        if(target.first < 0 || target.second < 0 || target.first >= m || target.second >= n)
            continue;

        if(map[target.first][target.second] == 0)
        {
            map[target.first][target.second] = 3;
            dfs(map, target.first, target.second);
        }
    }    
}

int subproblem(vector<vector<int>> & map)
{
    int m = map.size();
    int n = map[0].size();

    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(map[i][j] == 2)
                dfs(map, i, j);
        }
    }

    int count = 0;

    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(map[i][j] == 0)
            {
                ++count;
            }

            if(map[i][j] == 3)
            {
                map[i][j] = 0;
            }
        }
    }

    return count;
}

int main()
{
    int m, n;
    cin >> m >> n;
    vector<vector<int>> map(m, vector<int>(n, 0));

    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            cin >> map[i][j];
        }
    }

    int _max = 0;

    for(int i=0;i<n*m;++i)
    {
        pair<int,int> posA = {i/n, i%n};
        if(map[posA.first][posA.second] != 0) continue;
        map[posA.first][posA.second] = 1;

        for(int j=0;j<n*m;++j)
        {
            pair<int,int> posB = {j/n, j%n};
            if(map[posB.first][posB.second] != 0) continue;
            map[posB.first][posB.second] = 1;

            for(int k=0;k<n*m;++k)
            {
                pair<int,int> posC = {k/n, k%n};
                if(map[posC.first][posC.second] != 0) continue;
                map[posC.first][posC.second] = 1;

                _max = max(_max, subproblem(map));
                map[posC.first][posC.second] = 0;
            }
            map[posB.first][posB.second] = 0;
        }
        map[posA.first][posA.second] = 0;
    }

    cout << _max << endl;

    return 0;
}