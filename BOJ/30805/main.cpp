#include <iostream> 
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main()
{
    int m, n;
    cin >> m;
    vector<int> a(m);

    for(int i=0;i<m;++i)
    {
        cin >> a[i];
    }

    cin >> n;
    vector<int> b(n);

    for(int i=0;i<n;++i)
    {
        cin >> b[i];
    }

    vector<int> result(m+1, 0);
    vector<vector<int>::iterator> pos(m, b.begin());
    int currentLen = 0;

    for(int i=0;i<m;++i)
    {
        vector<int>::iterator findResult = find(b.begin(), b.end(), a[i]);
        bool finish = false;

        while(findResult != b.end() && !finish)
        {
            vector<int>::iterator location = upper_bound(result.begin(), result.begin()+currentLen, a[i], greater<int>());
            
            if(location == result.begin() || pos[location - result.begin() - 1] < findResult)
            {
                currentLen = location - result.begin() + 1;
                *location = a[i];
                pos[currentLen - 1] = findResult;
                finish = true;
            }
            findResult = find(findResult+1, b.end(), a[i]);
        }
    }

    cout << currentLen << endl;

    for(int i=0;i<currentLen;++i)
        cout << result[i] << " ";
    cout << endl;

    return 0;
}