#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n,d,k,c;
    cin >> n >> d >> k >> c;

    int maxCount = 0;

    queue<int> order;
    vector<int> firstChobabs(k);
    unordered_map<int, int> count;
    count[c] = 1;
    for(int i=0;i<k;++i)
    {
        int chobab;
        cin >> chobab;

        firstChobabs[i] = chobab;
        order.push(chobab);
        ++count[chobab];
    }
    maxCount = max(maxCount, (int)count.size());
    for(int i=k;i<n;++i)
    {
        int exclusion = order.front();
        order.pop();

        --count[exclusion];

        if(count[exclusion] == 0)
            count.erase(exclusion);

        int chobab;
        cin >> chobab;

        order.push(chobab);
        ++count[chobab];    

        maxCount = max(maxCount, (int)count.size());
    }
    for(int i=0;i<k;++i)
    {
        int exclusion = order.front();
        order.pop();

        --count[exclusion];

        if(count[exclusion] == 0)
            count.erase(exclusion);

        int chobab = firstChobabs[i];
        order.push(chobab);
        ++count[chobab];

        maxCount = max(maxCount, (int)count.size());
    }

    cout << maxCount << endl;

    return 0;
}