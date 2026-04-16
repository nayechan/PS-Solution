#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n, m;
    cin >> n;
    vector<int> data(n);

    for(int i=0;i<n;++i)
    {
        cin >> data[i];
    }

    cin >> m;

    vector<int> indice(n);
    for(int i=0;i<n;++i)
    {
        indice[i] = i;
    }

    sort(indice.begin(), indice.end(), [&data](int a, int b){
        return data[a] < data[b];
    });

    int maxZero = indice[0];
    int maxOne = (indice[0] == 0 && n > 1) ? indice[1] : indice[0];

    string result = "";

    if(data[maxOne] <= m)
    {
        result += to_string(maxOne);
        m -= data[maxOne];
        while(m >= data[maxZero])
        {
            result += to_string(maxZero);
            m -= data[maxZero];
        }
    }

    int maxLen = result.size();

    for(int i=0;i<maxLen;++i)
    {
        m += data[result[i] - '0'];
        for(int j=n-1;j>=0;--j)
        {
            if(m >= data[j])
            {
                m -= data[j];
                result[i] = j + '0';
                break;
            }
        }
    }

    if (result.size() == 0) result = "0";

    cout << result << endl;

    return 0;
}