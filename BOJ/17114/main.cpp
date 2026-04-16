#include <iostream>
#include <vector>
#include <array>
#include <queue>

using namespace std;

int dimDelta(int i, const array<int, 11> & dim)
{
    int currentMult = 1;

    for(int j=0;j<i;++j)
    {
        currentMult *= dim[j];
    }

    return currentMult;
}

int retrieveMultidimensionalIndex(int index, const array<int, 11> & dim, int i)
{
    int _index;
    
    for(int j=0;j<=i;++j)
    {
        _index = index % dim[j];
        index /= dim[j];
    }

    return _index;
}

int maxIndex(const array<int, 11> & dim)
{
    int mult = 1;
    for(auto e : dim)
    {
        mult *= e;
    }
    return mult;
}

int simulateTomatoes(const array<int, 11> & dim, int * map, int tomatoCount, int max)
{
    const array<int, 2> delta = {-1, 1};
    queue<int> tomatoQueue;

    int n = max;
    bool * visited = new bool[n];

    for(int i=0;i<n;++i)
    {
        if(map[i] == 1)
        {
            tomatoQueue.push(i);
            visited[i] = true;
        }
        else
        {
            visited[i] = false;
        }
    }

    int day = 0;

    while(!tomatoQueue.empty())
    {
        int size = tomatoQueue.size();
        while(size > 0)
        {
            auto currentTomato = tomatoQueue.front();
            tomatoQueue.pop();

            for(int i=0;i<11;++i)
            {
                auto currentTomatoPart = retrieveMultidimensionalIndex(currentTomato, dim, i);
                for(auto & d : delta)
                {
                    currentTomatoPart += d;
                    int unidimensionalIndex = currentTomato + (dimDelta(i, dim) * d);

                    if(0 <= currentTomatoPart && currentTomatoPart < dim[i] && 
                        !visited[unidimensionalIndex] && map[unidimensionalIndex] != -1)
                    {                        
                        tomatoQueue.push(unidimensionalIndex);
                        map[unidimensionalIndex] = 1;
                        visited[unidimensionalIndex] = true;
                    }
                    currentTomatoPart -= d;
                }              
            }
            --size;
        }
        ++day;
    }

    for(int i=0; i<max; ++i)
    {
        auto tomato = map[i];
        if(tomato == 0)
            return -1;
    }

    return day - 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int tomatoCount = 0;
    array<int, 11> dim;

    for(int i=0;i<11;++i)
    {
        cin >> dim[i];
    }

    int max = maxIndex(dim);
    int i = 0;
    
    int * map = new int[max];

    while(i<max)
    {
        cin >> map[i];

        if(map[i] != -1) 
            ++tomatoCount;
        ++i;
    }

    cout << simulateTomatoes(dim, map, tomatoCount, max) << endl;

    return 0;
}
