#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

bool isValid(pair<int, int> x, int n)
{
    if (x.first < 0 || x.second < 0) return false;
    if (x.first >= n || x.second >= n) return false;
    return true;
}

pair<int, pair<int, int>> findNearestPoint(const vector<vector<int>>& map, const pair<int, int>& shark, int size)
{
    int n = map.size();
    vector<vector<bool>> visit(n, vector<bool>(n, false));

    const vector<pair<int, int>> delta = { {-1,0},{0,-1},{0,1},{1,0} };

    queue<pair<int, pair<int, int>>> target;

    visit[shark.first][shark.second] = true;

    for (const auto& _delta : delta)
    {
        pair<int, int> pos = { shark.first + _delta.first, shark.second + _delta.second };
        if (isValid(pos, n))
        {
            target.push({ 1, pos });
        }
    }

    pair<int, pair<int, int>> result = { INT_MAX, {INT_MAX, INT_MAX} };

    while (!target.empty())
    {
        const auto _target = target.front();
        target.pop();

        int r = _target.second.first;
        int c = _target.second.second;
        int dist = _target.first;

        if (visit[r][c]) continue;

        visit[r][c] = true;

        int element = map[r][c];

        if (element == 0 || element == size)
        {
            for (const auto& _delta : delta)
            {
                pair<int, int> pos = { r + _delta.first, c + _delta.second };
                if (isValid(pos, n) && !visit[pos.first][pos.second])
                {
                    target.push({ dist + 1, pos });
                }
            }
        }
        else if (element < size)
        {
            if (dist < result.first)
            {
                result = _target;
            }
            else if (dist == result.first && r < result.second.first)
            {
                result = _target;
            }
            else if (dist == result.first && r == result.second.first && c <= result.second.second)
            {
                result = _target;
            }
        }
    }

    return result;
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> map(n, vector<int>(n));

    pair<int, int> shark;

    for (int i = 0;i < n;++i)
    {
        for (int j = 0;j < n;++j)
        {
            cin >> map[i][j];
            if (map[i][j] == 9)
            {
                shark = { i,j };
                map[i][j] = 0;
            }
        }
    }

    pair<int, pair<int, int>> nextPosData;
    int size = 2;
    int exp = 0;
    int dist = 0;
    while (true) {
        nextPosData = findNearestPoint(map, shark, size);
        if (nextPosData.first != INT_MAX)
        {
            ++exp;

            if (exp >= size)
            {
                exp -= size;
                ++size;
            }

            pair<int, int> nextPos = nextPosData.second;

            dist += nextPosData.first;
            //cout << map[nextPos.first][nextPos.second] << " / ";
            map[nextPos.first][nextPos.second] = 0;
            shark = nextPos;
            //cout << "(" << shark.first << ", " << shark.second << ") " << dist << " " << size << endl;
        }
        else
        {
            break;
        }
    }

    cout << dist << endl;
    return 0;
}