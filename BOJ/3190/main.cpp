#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void printBoard(vector<vector<int>>& board)
{
    for (auto& line : board)
    {
        for (auto& item : line)
            cout << item << " ";
        cout << endl;
    }
    cout << endl;
}

int main()
{
    int n, k;
    cin >> n >> k;

    vector<vector<int>> board(n, vector<int>(n, 0));

    for (int i = 0;i < k;++i)
    {
        int r, c;
        cin >> r >> c;

        board[r - 1][c - 1] = 1;
    }

    int l;
    cin >> l;
    queue<pair<int, char>> movement;

    for (int i = 0;i < l;++i)
    {
        pair<int, char> data;
        cin >> data.first >> data.second;
        movement.push(data);
    }

    int result = 0;
    int length = 1;
    pair<int, int> position = { 0,0 };
    int rotation = 0;
    vector<pair<int, int>> delta = { {0,1},{1,0},{0,-1},{-1,0} };
    queue<pair<int, int>> worm;
    worm.push(position);

    board[0][0] = 2;

    while (true)
    {
        ++result;
        pair<int,char> _movement = { -1, 'L' };

        if(!movement.empty())
            _movement = movement.front();

        auto _delta = delta[rotation];

        position = {
            position.first + _delta.first,
            position.second + _delta.second
        };

        if (
            position.first < 0 || position.second < 0 ||
            position.first >= n || position.second >= n
            )
        {
            break;
        }

        worm.push(position);
        
        if (board[position.first][position.second] == 2)
        {
            break;
        }

        if (board[position.first][position.second] == 1)
        {
            ++length;
        }
        else
        {
            pair<int, int> removePosition = worm.front();
            worm.pop();
            board[removePosition.first][removePosition.second]
                = 0;
        }

        board[position.first][position.second] = 2;

        if (_movement.first != -1 && _movement.first == result)
        {
            if (_movement.second == 'D')
            {
                ++rotation;
            }
            else if (_movement.second == 'L')
            {
                --rotation;
            }
            rotation %= delta.size();
            movement.pop();
        }
    }

    cout << result;
}