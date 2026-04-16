#include <iostream>
#include <vector>

using namespace std;

struct Sticker {
    int row, column, count;
    vector<vector<bool>> stickerData;

    Sticker()
    {
        row = 0;
        column = 0;
        count = 0;
    }

    Sticker(int row, int column)
    {
        this->row = row;
        this->column = column;
        
        count = 0;

        stickerData = vector<vector<bool>>(row, vector<bool>(column, false));
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < column; ++j)
            {
                int status = 0;
                cin >> status;

                if (status == 1)
                {
                    stickerData[i][j] = true;
                    ++count;
                }
            }
        }
    }

    static Sticker MakeRotatedSticker(const Sticker& other)
    {
        Sticker sticker;
        sticker.row = other.column;
        sticker.column = other.row;
        sticker.count = other.count;

        sticker.stickerData = vector<vector<bool>>(sticker.row, vector<bool>(sticker.column, false));
        for (int i = 0; i < sticker.row; ++i)
        {
            for (int j = 0; j < sticker.column; ++j)
            {
                sticker.stickerData[i][j] = other.stickerData[sticker.column - j - 1][i];
            }
        }

        return sticker;
    }
};

struct Notebook {
    int row, column;
    vector<vector<bool>> notebookData;

    Notebook(int maxRow, int maxColumn) {
        row = maxRow;
        column = maxColumn;

        notebookData = vector<vector<bool>>(row, vector<bool>(column, false));
    }

    // return true if overlap occurs
    bool verifyOverlap(Sticker& sticker, int _i, int _j)
    {
        for (int i = 0; i < sticker.row; ++i)
        {
            for (int j = 0; j < sticker.column; ++j)
            {
                if (sticker.stickerData[i][j] && notebookData[i + _i][j + _j])
                {
                    return true;
                }
            }
        }
        return false;
    }

    void assignSticker(Sticker& sticker, int _i, int _j)
    {
        for (int i = 0; i < sticker.row; ++i)
        {
            for (int j = 0; j < sticker.column; ++j)
            {
                if (sticker.stickerData[i][j])
                    notebookData[i + _i][j + _j] = true;
            }
        }
    }


    int tryAssignSticker(vector<Sticker>& sticker)
    {
        for (int rotation = 0; rotation < 4; ++rotation)
        {
            for (int i = 0; i <= row - sticker[rotation].row; ++i)
            {
                for (int j = 0; j <= column - sticker[rotation].column; ++j)
                {
                    if (!verifyOverlap(sticker[rotation], i, j))
                    {
                        assignSticker(sticker[rotation], i, j);
                        // assign success
                        return sticker[rotation].count;
                    }
                }
            }
        }

        // assign failed
        return 0;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int row, column, stickerCount;
    cin >> row >> column >> stickerCount;

    Notebook notebook(row, column);

    vector<vector<Sticker>> stickers(stickerCount);

    int successCount = 0;

    for (int i = 0; i < stickerCount; ++i)
    {
        stickers[i].reserve(4);
    }

    for (int i = 0; i < stickerCount; ++i)
    {
        int _row, _column;
        cin >> _row >> _column;

        Sticker newSticker = Sticker(_row, _column);
        for (int j = 0; j < 4; ++j)
        {
            if (j != 0)
                newSticker = Sticker::MakeRotatedSticker(newSticker);

            stickers[i].push_back(newSticker);
        }

        int result = notebook.tryAssignSticker(stickers[i]);
        successCount += result;
    }

    cout << successCount << '\n';

    return 0;
}