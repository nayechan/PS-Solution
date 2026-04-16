#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    scanf("%d",&n);

    vector<int> seq = vector<int>(n);
    vector<int> nge_index = vector<int>(n, -1);
    for(int i=0;i<n;++i)
    {
        scanf("%d",&seq[i]);
    }

    for(int i=nge_index.size()-1; i>=0; --i)
    {
        int lookup = i+1;
        int result = -1;
        while(true)
        {
            if(lookup >= nge_index.size())
                break;

            if(seq[i] < seq[lookup])
            {
                nge_index[i] = lookup;
                break;
            }
            lookup = nge_index[lookup];
        }
    }

    for(auto element : nge_index)
    {
        if(element == -1) printf("-1 ");
        else printf("%d ",seq[element]);
    }



    /*
    3 5 2 7
    5 7 7 -1
    */
    return 0;
}