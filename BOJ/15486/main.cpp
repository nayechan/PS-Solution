#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int work(vector<pair<int,int>> & work_data, vector<int> & cached_data, int d, int max_day);

int main()
{
    vector<pair<int, int>> work_data;
    vector<int> cached_data;

    int n;

    scanf("%d",&n);
    work_data = vector<pair<int, int>>(n+1, {0,0});
    cached_data = vector<int>(n+2, -1);
    
    for(int i=1;i<=n;++i)
    {
        scanf("%d %d",&(work_data[i].first), &(work_data[i].second));
    }

    printf("%d", work(work_data, cached_data, 1, n));

    return 0;
}


int work(vector<pair<int,int>> & work_data, vector<int> & cached_data, int d, int max_day)
{

    if(d > max_day) return 0;
    if(cached_data[d] != -1) return cached_data[d];


    int a = work(work_data, cached_data, d+1, max_day);
    int b = 0;
    
    if(d+work_data[d].first <= max_day+1)
        b = work(work_data, cached_data, d+work_data[d].first, max_day) + work_data[d].second;

    int result = max(a,b);
    cached_data[d] = result;

    return cached_data[d];    
}