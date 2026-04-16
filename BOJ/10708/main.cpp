#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int m, n;
    cin >> n >> m;

    vector<int> target(m);
    vector<int> score(n, 0);

    for(int i=0;i<m;++i)
    {
        cin >> target[i];
    }

    for(int i=0;i<m;++i)
    {
        int bonus = 0;
        for(int j=0;j<n;++j)
        {
            int assumption;

            cin >> assumption;

            if(target[i] == assumption)
                ++score[j];
            else
                ++bonus;
        }
        score[target[i]-1] += bonus;
    }

    for(int i=0;i<n;++i)
    {
        cout << score[i] << endl;
    }

    return 0;
}