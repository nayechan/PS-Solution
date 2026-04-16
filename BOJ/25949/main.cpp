#include <iostream>
#include <array>
#include <map>

using namespace std;

array<array<array<array<int, 100>,100>,100>,50> arrA;
array<array<array<array<int, 100>,100>,100>,50> arrB;
array<array<array<array<bool, 100>,100>,100>,50> isUsed = {false,};

void updateResult(pair<int,int> & totalResult, pair<int,int> & result, bool turn, int diff)
{
    if(!turn)
    {
        result.first += diff;
        if(result.first > totalResult.first)
            totalResult = result;
    }
    else
    {
        result.second += diff;
        if(result.second > totalResult.second)
            totalResult = result;
    }
}

// 100 * 100 * 100 = 4mb
pair<int,int> game(int a, int b, int c, int turnCount)
{
    if(isUsed[a][b][c][turnCount])
        return {arrA[a][b][c][turnCount], arrB[a][b][c][turnCount]};

    bool turn = turnCount % 2 == 0;
    if(a == 0 && b == 0 && c == 0)
    {
        arrA[a][b][c][turnCount] = 0;
        arrB[a][b][c][turnCount] = 0;
        isUsed[a][b][c][turnCount] = true;
        return {0,0};
    }

    pair<int,int> totalResult = {0,0};

    if(a!=0)
    {
        int diff = min(turnCount, a);
        auto result = game(a-diff, b, c, turnCount+1);
        updateResult(totalResult, result, turn, diff);
    }

    if(b!=0)
    {
        int diff = min(turnCount, b);
        auto result = game(a, b-diff, c, turnCount+1);
        updateResult(totalResult, result, turn, diff);        
    }

    if(c!=0)
    {
        int diff = min(turnCount, c);
        auto result = game(a, b, c-diff, turnCount+1);
        updateResult(totalResult, result, turn, diff);
    }

    arrA[a][b][c][turnCount] = totalResult.first;
    arrB[a][b][c][turnCount] = totalResult.second;
    isUsed[a][b][c][turnCount] = true;

    return totalResult;
}

int main()
{
    int a, b, c;
    cin >> a >> b >> c;

    auto result = game(a,b,c,1);

    if(result.first < result.second)
    {
        cout << "S" << endl;
    }
    else if(result.first > result.second)
    {
        cout << "F" << endl;
    }
    else
        cout << "D" << endl;

    return 0;
}