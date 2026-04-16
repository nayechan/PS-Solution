#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main()
{
    int n,m;
    cin >> n >> m;

    vector<int> caseCount(n+1, 0);
    set<pair<int,int>> target;

    for(int i=0;i<=n;++i)
    {
        caseCount[i][0] = 1;
    }

    for(int i=0;i<=m;++i)
    {
        caseCount[0][i] = 1;
    }

    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            for(int )
        }
    }

    for(int i=1;i<=m;++i)
        cout << caseCount[i] << " ";
    cout << endl;

    return 0;
}