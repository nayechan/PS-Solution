#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <list>

using namespace std;

constexpr int searchDepth = 10;

void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            cout << cell << "\t";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool fall(vector<vector<int>>& board, int direction, int& outputMax, int& outputSum)
{
    // 0 : down, 1 : right, 2 : up, 3 : left
    int n = board.size();
    int max = 0;
    int sum = 0;

    bool isEqual = true;

    stack<int> line;

    if (direction == 0)
    {
        for (int j = 0;j < n;++j)
        {
            for (int i = 0;i < n;++i)
            {
                if (board[i][j] != 0)
                    line.push(board[i][j]);
            }

            deque<int> result;
            while (!line.empty())
            {
                int first = line.top(); line.pop();

                if (!line.empty() && first == line.top())
                {
                    first += line.top(); line.pop();
                }

                max = (max < first) ? first : max;
                sum += first;

                result.push_front(first);
            }
            while (result.size() < n)
            {
                result.push_front(0);
            }

            for (int i = 0;i < n;++i)
            {
                if (board[i][j] != result[i]) isEqual = false;
                board[i][j] = result[i];
            }
        }
    }
    else if (direction == 1)
    {
        for (int i = 0;i < n;++i)
        {
            for (int j = 0;j < n;++j)
            {
                if (board[i][j] != 0)
                    line.push(board[i][j]);
            }

            deque<int> result;
            while (!line.empty())
            {
                int first = line.top(); line.pop();

                if (!line.empty() && first == line.top())
                {
                    first += line.top(); line.pop();
                }

                max = (max < first) ? first : max;
                sum += first;

                result.push_front(first);
            }
            while (result.size() < n)
            {
                result.push_front(0);
            }

            for (int j = 0;j < n;++j)
            {
                if (board[i][j] != result[j]) isEqual = false;
                board[i][j] = result[j];
            }
        }
    }
    else if (direction == 2)
    {
        for (int j = 0;j < n;++j)
        {
            for (int i = n - 1;i >= 0;--i)
            {
                if (board[i][j] != 0)
                    line.push(board[i][j]);
            }

            deque<int> result;
            while (!line.empty())
            {
                int first = line.top(); line.pop();

                if (!line.empty() && first == line.top())
                {
                    first += line.top(); line.pop();
                }

                max = (max < first) ? first : max;
                sum += first;

                result.push_back(first);
            }
            while (result.size() < n)
            {
                result.push_back(0);
            }

            for (int i = 0;i < n;++i)
            {
                if (board[i][j] != result[i]) isEqual = false;
                board[i][j] = result[i];
            }
        }
    }
    else
    {
        for (int i = 0;i < n;++i)
        {
            for (int j = n - 1;j >= 0;--j)
            {
                if (board[i][j] != 0)
                    line.push(board[i][j]);
            }

            deque<int> result;
            while (!line.empty())
            {
                int first = line.top(); line.pop();

                if (!line.empty() && first == line.top())
                {
                    first += line.top(); line.pop();
                }

                max = (max < first) ? first : max;
                sum += first;

                result.push_back(first);
            }
            while (result.size() < n)
            {
                result.push_back(0);
            }

            for (int j = 0;j < n;++j)
            {
                if (board[i][j] != result[j]) isEqual = false;
                board[i][j] = result[j];
            }
        }
    }

    outputMax = max;
    outputSum = sum;

    return isEqual;
}

int biggest(vector<vector<int>>& board)
{
    int result = 0;
    for (auto& line : board)
    {
        for (auto& item : line)
        {
            if (result < item) result = item;
        }
    }

    return result;
}

int sum(vector<vector<int>>& board)
{
    int result = 0;
    for (auto& line : board)
    {
        for (auto& item : line)
        {
            result += item;
        }
    }

    return result;
}

int simulate(vector<vector<int>>& board, int searchDepth, int max = 0) {
    if (max == 0)
    {
        max = biggest(board);
    }

    if (searchDepth == 0)
    {
        return max;
    }

    vector<vector<int>> boardBackup(board);
    for (int i = 0;i < 4;++i) {

        int localMax = 0, localSum = 0;
        bool isEqual = fall(board, i, localMax, localSum);

        if (isEqual)
            continue;

        if (localSum < max * 2)
            continue;

        if (localMax != 0) {
            int result = simulate(board, searchDepth - 1, localMax);
            if (max < result) max = result;
        }

        board = boardBackup;
    }
    return max;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<vector<int>> board(n, vector<int>(n, 0));

    for (int i = 0;i < n;++i)
    {
        for (int j = 0;j < n;++j)
        {
            cin >> board[i][j];
        }
    }

    cout << simulate(board, searchDepth) << endl;

    return 0;
}