#include <iostream>
#include <cstring>

using namespace std;

bool isValid(int value, int n)
{
    return value >= 0 && value < n;
}

void SwitchLight(bool arr[10][10], int switchCount[10][10], int _i, int _j)
{
    int dx[] = {0, 0, 1, -1, 0};
    int dy[] = {1, -1, 0, 0, 0};

    for(int index=0;index<5;++index)
    {
        int i = _i + dx[index];
        int j = _j + dy[index];

        if(isValid(i, 10) && isValid(j, 10))
        {
            arr[i][j] = !arr[i][j];
        }
    }
    ++switchCount[_i][_j];
}

int GetSwtichCount(bool arr[10][10], int firstRowData)
{
    bool lightData[10][10];
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            lightData[i][j] = arr[i][j];
        }
    }

    int switchCount[10][10] = {0, };

    for(int i=0;i<10;++i)
    {
        if (firstRowData & (1 << i))
        {
            SwitchLight(lightData, switchCount, 0, i);
        }
    }

    for(int i=1;i<10;++i)
    {
        for(int j=0;j<10;++j)
        {
            if(lightData[i-1][j])
                SwitchLight(lightData, switchCount, i, j);
        }
    }

    int _switchCount = 0;
    for(int i=0;i<10;++i)
    {
        for(int j=0;j<10;++j)
        {
            if(lightData[i][j])
            {
                return -1;
            }

            _switchCount += (switchCount[i][j] % 2);
        }
    }

    return _switchCount;
}

int GetSolution(bool arr[10][10])
{
    int min = -1;
    for(int firstRowData = 0; firstRowData < (1 << 10); ++firstRowData)
    {
        int switchCount = GetSwtichCount(arr, firstRowData);

        if(switchCount != -1)
        {
            if(min == -1 || min > switchCount)
            {
                min = switchCount;
            }
        }
    }

    return min;
}

int main()
{
    bool arr[10][10];

    for(int i=0;i<10;++i)
    {
        for(int j=0;j<10;++j)
        {
            arr[i][j] = getchar()=='O';
        }
        getchar();
    }

    int result = GetSolution(arr);

    printf("%d", result);

    return 0;
}