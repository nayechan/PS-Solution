#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> currentTab(n), validTab(n);

    for(int i=0;i<n;++i)
    {
        cin >> currentTab[i];
    }

    for(int i=0;i<n;++i)
    {
        cin >> validTab[i];
    }

    vector<int> diff(n);
    for(int i=0;i<n;++i)
    {
        diff[i] = validTab[i] - currentTab[i];
    }



    int sum = 0;
    do{
        cout << "===" << endl;
        queue<pair<int,int>> status;

        status.push({0,n-1});
        int newStart = 0;    
        for(int i=0;i<n;++i)
        {
            if(diff[i] <= 0) 
            {
                if(newStart <= i-1) status.push({newStart, i-1});
                newStart = i+1;
            }
        }
    
        int count = status.size();
        for(int i=0;i<count;++i)
        {
            const auto& [start,end] = status.back();
            cout << start << " ~ " << end << endl;
            status.pop();
    
            for(int j=start; j<=end; ++j)
            {
                --diff[j];
                sum += abs(diff[j]);
            }
        }
    }while(sum!=0);

        

    return 0;
}
