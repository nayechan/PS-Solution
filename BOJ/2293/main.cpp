#include <iostream>
#include <vector>

using namespace std;

int retreive(vector<int> & coins, vector<int> & cached_data, int cost);

int main()
{
    int n, k;
    scanf("%d %d",&n,&k);
    vector<int> coin;
    vector<int> cached_data = vector<int>(k+1, 0);

    for(int i=0;i<n;++i)
    {
        int input;
        scanf("%d",&input);
        coin.push_back(input);
    }

    printf("%d\n", retreive(coin, cached_data, k));

    return 0;
}

int retreive(vector<int> & coins, vector<int> & cached_data, int cost)
{
    if(cost < 0)
        return 0;

    if(cost == 0)
        return 1;
    
    int sum = 0;
    int index = 0;
    
    cached_data[0] = 1;

    for(auto coin : coins)
    {
        for(int i = 1; i <= cost; ++i)
        {
            int targetIndex = i - coin;

            if(targetIndex >= 0)
                cached_data[i] += cached_data[targetIndex];
        }
    }
    return cached_data[cost];
}

/*
0 1 2 3 4 5 6 7 8 9 10
1 1 2 2 3 4 4 4 5 5 10

1 1 1 1 1 1 1 1 1 1 1
1 1 2 2 3 3 4 4 5 5 6
1 1 2 2 3 4 5 6 7 8 10

1 1 2 3
*/