#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <memory.h>

int dp[1001][1001];

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    if (n < m) swap(&n, &m);

    for (int i = 0;i <= n;++i)
    {
        for (int j = 0; j <= m; ++j)
        {
            if (i == 0 || j == 0) dp[i][j] = 0;
            else if (i == 1) dp[i][j] = j;
            else if (j == 1) dp[i][j] = i;
            else if (i == j) dp[i][j] = 1;
            else dp[i][j] = 999999999;
        }
    }

    for (int i = 2;i <= n; ++i)
    {
        for (int squareSize = 1;squareSize*2 <= i;++squareSize)
        {
            for (int j = 2; j <= m; ++j)
            {
                int newValue = dp[squareSize][j] + dp[i - squareSize][j];
                if (dp[i][j] > newValue) dp[i][j] = newValue;
            }
        }
        for (int j = 2; j <= m; ++j)
        {
            for (int squareSize = 1;squareSize*2 <= j;++squareSize)
            {
                int newValue = dp[i][squareSize] + dp[i][j - squareSize];
                if (dp[i][j] > newValue) dp[i][j] = newValue;
            }
        }
    }



    printf("%d\n", dp[n][m]);
    return 0;
}