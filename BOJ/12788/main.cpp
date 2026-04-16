#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    priority_queue<int> pq;
    for(int i=0;i<n;++i)
    {
        int input;
        cin >> input;
        pq.push(input);
    }

    int diff = m * k;
    int count = 0;
    while(!pq.empty() && diff > 0)
    {
        int _max = pq.top(); pq.pop();

        ++count;
        diff -= _max;
    }

    if (diff <= 0)
        cout << count << endl;

    else
        cout << "STRESS" << endl;

    return 0;
}