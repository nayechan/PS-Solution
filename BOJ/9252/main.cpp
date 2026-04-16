#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{
    string a, b;
    cin >> a >> b;

    int m = a.size(), n = b.size();

    vector<vector<int>> seqCount(m, vector<int>(n, 0));

    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(a[i] == b[j])
            {
                if(i == 0 || j == 0)
                    seqCount[i][j] = 1;
                
                else
                    seqCount[i][j] = seqCount[i-1][j-1] + 1;
            }
            else
            {
                int seqA = 0, seqB = 0;
                if(i != 0)
                {
                    seqA = seqCount[i-1][j];
                }
                if(j != 0)
                {
                    seqB = seqCount[i][j-1];
                }
                seqCount[i][j] = max(seqA, seqB);
            }
        }
    }

    int maxLength = seqCount[m-1][n-1];
    cout << maxLength << endl;

    stack<char> result;
    pair<int, int> pos = {m-1, n-1};

    while(maxLength > 0)
    {
        maxLength = seqCount[pos.first][pos.second];

        if(maxLength == 0) break;

        if(pos.first > 0 && seqCount[pos.first-1][pos.second] == maxLength)
        {
            --pos.first;
            continue;
        }
        if(pos.second > 0 && seqCount[pos.first][pos.second-1] == maxLength)
        {
            --pos.second;
            continue;
        }

        result.push(a[pos.first]);
        --pos.first; --pos.second;

        if(pos.first < 0 || pos.second < 0)
            break;
    }

    while(!result.empty())
    {
        cout << result.top();
        result.pop();
    }

    return 0;
}