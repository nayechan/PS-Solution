#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    vector<vector<int>> data(n, vector<int>(m, 0));

    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, { -1,-1 }));

    // to distinct unassigned position using {-1, -1}
    pair<int, int> start = { -1, -1 }, end = { -1, -1 };

    for (int row = 0; row < n; ++row)
    {
        string input;
        cin >> input;

        int column = 0;
        for (char ch : input)
        {
            data[row][column] = (ch == '+') ? 1 : 0;

            if (row == 0 || row == n - 1 || column == 0 || column == m - 1)
            {
                if (ch == '.')
                {
                    if (start.first < 0)
                        start = { row, column };
                    else
                        end = { row, column };
                }
            }
            ++column;
        }
    }

    queue<pair<int, int>> targetPositions;
    const vector<pair<int, int>> delta = { {0,1},{0,-1},{1,0},{-1,0} };

    targetPositions.push(start);
    parent[start.first][start.second] = start;

    bool found = false;

    while (!targetPositions.empty() && !found)
    {
        int count = targetPositions.size();

        for (int round = 1; round <= count; ++round)
        {
            pair<int, int> element = targetPositions.front();
            for (const pair<int, int>& d : delta)
            {
                pair<int, int> targetPos = {
                    element.first + d.first,
                    element.second + d.second
                };

                if (targetPos.first < 0 || targetPos.first >= n)
                    continue;

                if (targetPos.second < 0 || targetPos.second >= m)
                    continue;

                if (data[targetPos.first][targetPos.second] != 0)
                    continue;

                targetPositions.push(targetPos);

                data[targetPos.first][targetPos.second] = 2;
                parent[targetPos.first][targetPos.second] = { element.first, element.second };

                if (targetPos == end)
                {
                    found = true;
                    break;
                }
            }

            targetPositions.pop();

            if (found)
            {
                break;
            }
        }
    }

    pair<int, int> cursor = end;
    data[end.first][end.second] = 3;

    while (cursor != start)
    {
        cursor = parent[cursor.first][cursor.second];
        data[cursor.first][cursor.second] = 3;
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (data[i][j] == 1)
                cout << "+";
            else if (data[i][j] == 3)
                cout << ".";
            else
                cout << "@";
        }
        cout << endl;
    }


    return 0;
}