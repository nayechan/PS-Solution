#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{
    string a, b, c;
    cin >> a >> b >> c;

    int m = a.size(), n = b.size(), p=c.size();

    vector<vector<vector<int>>> seqCount(m, vector<vector<int>>(n, vector<int>(p, 0)));

    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            for(int k=0;k<p;++k)
            {
                if(a[i] == b[j] && b[j] == c[k])
                {
                    if(i == 0 || j == 0 || k == 0)
                        seqCount[i][j][k] = 1;
                    
                    else
                        seqCount[i][j][k] = seqCount[i-1][j-1][k-1] + 1;
                }
                else
                {
                    int seqA = 0, seqB = 0, seqC = 0;

                    if(i != 0)
                        seqA = seqCount[i-1][j][k];
                    if(j != 0)
                        seqB = seqCount[i][j-1][k];
                    if(k != 0)
                        seqC = seqCount[i][j][k-1];

                    seqCount[i][j][k] = max(max(seqA, seqB), seqC);
                }
            }
            
        }
    }

    int maxLength = seqCount[m-1][n-1][p-1];
    cout << maxLength << endl;

    return 0;
}