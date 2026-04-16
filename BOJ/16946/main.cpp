#include <iostream>
#include <vector>
#include <set>

using namespace std;

void dfs(vector<vector<int>>& map, set<pair<int, int>>& result, int i, int j)
{
    if (i < 0 || j < 0 || i >= map.size() || j >= map[0].size())
        return;
    if (map[i][j] != 0)
        return;
    if (result.find({ i,j }) != result.end())
        return;

    vector<pair<int, int>> delta = { {0,1},{0,-1},{1,0},{-1,0} };

    result.insert({ i,j });
    for (const auto& _delta : delta)
    {
        dfs(map, result, i + _delta.first, j + _delta.second);
    }
}

bool floodFill(vector<vector<int>>& map, vector<vector<int>>& result, int i, int j, int n)
{
    if (i < 0 || j < 0 || i >= map.size() || j >= map[0].size())
        return false;


    if (map[i][j] != 0)
        return false;

    set<pair<int, int>> block;
    dfs(map, block, i, j);

    int blockSize = block.size();
    for (const auto& element : block)
    {
        result[element.first][element.second] = blockSize;
        map[element.first][element.second] = n;
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int m, n;
    cin >> m >> n;
    vector<vector<int>> map(m, vector<int>(n));
    vector<vector<int>> result(m, vector<int>(n, 0));
    vector<vector<int>> final_result(m, vector<int>(n, 0));

    vector<pair<int, int>> delta = { {0,1},{0,-1},{1,0},{-1,0} };

    for (int i = 0;i < m;++i)
    {
        string str;
        cin >> str;
        int j = 0;
        for (char ch : str)
        {
            map[i][j] = ch - '0';
            ++j;
        }
    }

    int blockIndex = 2;
    for (int i = 0;i < m;++i)
    {
        for (int j = 0;j < n;++j)
        {
            for (const auto& _delta : delta)
            {
                if (floodFill(map, result, i + _delta.first, j + _delta.second, blockIndex))
                {
                    ++blockIndex;
                }
            }
        }
    }
    for (int i = 0;i < m;++i)
    {
        for (int j = 0;j < n;++j)
        {
            if (map[i][j] > 1)
            {
                cout << "0";
                continue;
            }
            int sum = 1;
            set<int> visitedBlock;
            for (const auto& _delta : delta)
            {
                int x = i + _delta.first;
                int y = j + _delta.second;           

                if (x < 0 || x >= result.size()) continue;
                if (y < 0 || y >= result[0].size()) continue;
                if (map[x][y] == 1) continue;
                if (visitedBlock.find(map[x][y]) != visitedBlock.end())
                    continue;

                sum += result[i + _delta.first][j + _delta.second];
                visitedBlock.insert(map[x][y]);
            }
            cout << sum;
        }
        cout << endl;
    }


    return 0;
}